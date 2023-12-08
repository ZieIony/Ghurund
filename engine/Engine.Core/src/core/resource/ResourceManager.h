#pragma once

#include "Loader.h"
#include "LoaderCollection.h"
#include "ReloadTask.h"
#include "Resource.h"
#include "ResourceFormat.h"
#include "ResourcePath.h"
#include "Resources.h"

#include "core/Buffer.h"
#include "core/Exceptions.h"
#include "core/Noncopyable.h"
#include "core/Object.h"
#include "core/collection/HashMap.h"
#include "core/logging/Logger.h"
#include "core/logging/Formatter.h"
#include "core/io/File.h"
#include "core/io/LibraryList.h"
#include "core/io/MemoryStream.h"
#include "core/io/watcher/FileWatcher.h"
#include "core/reflection/Type.h"
#include "core/threading/WorkerThread.h"

#include <format>

namespace Ghurund::Core {
	class ResourceManager:public Noncopyable, public Object {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ResourceManager::GET_TYPE();
#pragma endregion

	private:
		FileWatcher watcher;
		Resources resources;
		mutable Map<ResourcePath, std::shared_ptr<Buffer>> resourceCache;
		LibraryList libraries;
		LoaderCollection loaders;

		WorkerThread loadingThread;
		List<ReloadTask*> reloadQueue;
		bool hotReloadEnabled
#ifdef _DEBUG
			= true;
#else
			= false;
#endif
		Loader* getLoader(const Ghurund::Core::Type& type) const;

		[[nodiscard]]
		Resource* load(
			Loader& loader,
			const File& file,
			const ResourceFormat* format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		);

		[[nodiscard]]
		Resource* load(
			Loader& loader,
			const ResourcePath& path,
			const DirectoryPath& workingDir,
			const ResourceFormat* format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		);

		Resource* loadInternal(
			Loader& loader,
			const DirectoryPath& workingDir,
			const ResourcePath& path,
			const ResourceFormat* format,
			LoadOption options
		);

		Resource* loadInternal(
			Loader& loader,
			const DirectoryPath& workingDir,
			const Buffer& buffer,
			const ResourceFormat* format,
			LoadOption options
		);

		void saveInternal(
			Resource& resource,
			const Loader& loader,
			const DirectoryPath& workingDir,
			Buffer& buffer,
			const ResourceFormat* format,
			SaveOption options
		) const;

	public:
		inline static const wchar_t* const ENGINE_LIB_NAME = L"Ghurund";
		inline static const wchar_t* const LIB_PROTOCOL = L"lib://";

		ResourceManager();

		~ResourceManager();

		inline LoaderCollection& getLoaders() {
			return loaders;
		}

		__declspec(property(get = getLoaders)) LoaderCollection& Loaders;

		inline void clearCache() {
			resources.clear();
			resourceCache.clear();
		}

		inline void removeFromCache(Resource* resource) {
			const ResourcePath* path = resource->Path;
			if (path) {
				resources.remove(*path);
				
			}
		}

		void reload();

		template<Derived<Resource> T>
		[[nodiscard]]
		T* load(const File& file, const ResourceFormat* format = ResourceFormat::AUTO, LoadOption options = LoadOption::DEFAULT) {
			Loader* loader = getLoader(Ghurund::Core::getType<T>());
			return (T*)load(*loader, file, format, options);
		}

		template<class T>
		void loadAsync(
			const File& file,
			const ResourceFormat* format = ResourceFormat::AUTO,
			std::function<void(T*)> onLoaded = nullptr,
			std::function<void(std::exception)> onError = nullptr,
			LoadOption options = LoadOption::DEFAULT
		) {
			SharedPointer<Task> task = makeShared<Task>(file.Path, [this, file, format, onLoaded, onError, options] {
				try {
					T* resource = load<T>(file, format, options);
					if (onLoaded)
						onLoaded((T*)resource);
				} catch (std::exception& e) {
					if (onError)
						onError(e);
					throw e;
				}
				});
			loadingThread.post(task.get());
		}

		template<Derived<Resource> T>
		[[nodiscard]]
		T* load(
			const ResourcePath& path,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat* format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) {
			Loader* loader = getLoader(Ghurund::Core::getType<T>());
			return (T*)load(*loader, path, workingDir, format, options);
		}

		template<class T>
		void loadAsync(
			const ResourcePath& path,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat* format = ResourceFormat::AUTO,
			std::function<void(T*)> onLoaded = nullptr,
			std::function<void(std::exception)> onError = nullptr,
			LoadOption options = LoadOption::DEFAULT
		) {
			SharedPointer<Task> task = makeShared<Task>(path, [this, path, workingDir, format, onLoaded, onError, options] {
				try {
					T* resource = load<T>(path, workingDir, format, options);
					if (onLoaded)
						onLoaded((T*)resource);
				} catch (std::exception& e) {
					if (onError)
						onError(e);
					throw e;
				}
				});
			loadingThread.post(task.get());
		}

		template<Derived<Resource> T>
		[[nodiscard]]
		T* load(
			const Buffer& buffer,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat* format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) {
			Loader* loader = getLoader(Ghurund::Core::getType<T>());
			return (T*)loadInternal(*loader, workingDir, buffer, format, options);
		}

		/*template<class T>
		void loadAsync(
			const Buffer& buffer,	// TODO: copy buffer?
			const DirectoryPath& workingDir,
			const ResourceFormat* format = ResourceFormat::AUTO,
			std::function<void(T*)> onLoaded = nullptr,
			std::function<void(std::exception)> onError = nullptr,
			LoadOption options = LoadOption::DEFAULT
		) {
			SharedPointer<Task> task = makeShared<Task>(path, [this, path, workingDir, format, onLoaded, onError, options] {
				try {
					T* resource = load(file, format, options);
					if (onLoaded)
						onLoaded((T*)resource);
				} catch (std::exception& e) {
					if (onError)
						onError(e);
					throw e;
				}
				});
			loadingThread.post(task.get());
		}*/

		template<Derived<Resource> T>
		void save(
			T& resource,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat* format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const {
			const Loader* loader = getLoader(Ghurund::Core::getType<T>());
			Buffer buffer;
			saveInternal(resource, *loader, buffer, format, options);
		}

		template<Derived<Resource> T>
		void save(
			T& resource,
			const ResourcePath& path,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat* format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const {
			resource.Path = &path;
			const Loader* loader = getLoader(Ghurund::Core::getType<T>());
			//Library* library = path.findLibrary(libraries);
			//if (library) {
				//auto buffer = path.resolveResource(workingDir, libraries);
				//saveInternal(resource, *loader, workingDir, buffer, format, options);
			//} else {
				Buffer buffer;
				saveInternal(resource, *loader, workingDir, buffer, format, options);
				File file(FilePath(path.toString()));
				file.write(buffer);
			//}
		}

		inline void setHotReloadEnabled(bool enabled) {
			this->hotReloadEnabled = enabled;
		}

		inline bool isHotReloadEnabled() const {
			return hotReloadEnabled;
		}

		__declspec(property(get = isHotReloadEnabled, put = setHotReloadEnabled)) bool HotReloadEnabled;

		LibraryList& getLibraries() {
			return libraries;
		}

		__declspec(property(get = getLibraries)) LibraryList& Libraries;
	};
}
