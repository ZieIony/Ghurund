#pragma once

#include "ReloadTask.h"
#include "Resource.h"
#include "ResourceCollection.h"
#include "ResourceFormat.h"

#include "core/Buffer.h"
#include "core/io/File.h"
#include "core/io/FilePath.h"
#include "core/io/LibraryCollection.h"
#include "core/io/watcher/FileWatcher.h"
#include "core/loading/Loader.h"
#include "core/loading/LoaderCollection.h"
#include "core/object/Noncopyable.h"
#include "core/object/Object.h"
#include "core/reflection/Type.h"
#include "core/threading/WorkerThread.h"


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
		ResourceCollection resources;
		mutable Map<WString, SharedPointer<Buffer>> resourceCache;
		LibraryCollection libraries;
		LoaderCollection loaders;

		WorkerThread loadingThread;
		List<ReloadTask*> reloadQueue;
		bool hotReloadEnabled
#ifdef _DEBUG
			= true;
#else
			= false;
#endif

		inline WString getCacheKey(const FilePath& path, const DirectoryPath& workingDir) const {
			return getAbsolutePath(path, workingDir).toString();
		}

		BaseLoader* getLoader(const Ghurund::Core::Type& type) const;

		[[nodiscard]]
		Resource* load(
			BaseLoader& loader,
			const FilePath& path,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		);

		Resource* loadInternal(
			BaseLoader& loader,
			const FilePath& path,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		);

		Resource* loadInternal(
			BaseLoader& loader,
			const Buffer& buffer,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		);

		void saveInternal(
			Resource& resource,
			const BaseLoader& loader,
			Buffer& buffer,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOption options
		) const;

	public:
		inline static const WString ENGINE_LIB_NAME = L"Ghurund";
		static const DirectoryPath ENGINE_LIB;
		inline static const WString LIB_PROTOCOL = L"lib://";

		ResourceManager();

		~ResourceManager();

		SharedPointer<Buffer> resolveResource(const FilePath& path, const DirectoryPath& workingDir) const;

		static inline FilePath getAbsolutePath(const FilePath& path, const DirectoryPath& workingDir) {
			return path.IsAbsolute ? path : (workingDir / path);
		}

		static inline DirectoryPath getLocalDir(const FilePath& path, const DirectoryPath& workingDir) {
			return getAbsolutePath(path, workingDir).Directory;
		}

		inline LoaderCollection& getLoaders() {
			return loaders;
		}

		__declspec(property(get = getLoaders)) LoaderCollection& Loaders;

		inline void clearCache() {
			resources.clear();
			resourceCache.clear();
		}

		inline void removeFromCache(Resource* resource, DirectoryPath workingDir) {
			const FilePath* path = resource->Path;
			if (path) {
				const WString cacheKey = getCacheKey(*path, workingDir);
				resources.remove(cacheKey);
			}
		}

		void reload();

		template<Derived<Resource> T>
		[[nodiscard]]
		T* load(
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) {
			BaseLoader* loader = getLoader(Ghurund::Core::getType<T>());
			return (T*)load(*loader, path, workingDir, format, options);
		}

		template<class T>
		void loadAsync(
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			std::function<void(T*)> onLoaded = nullptr,
			std::function<void(std::exception)> onError = nullptr,
			LoadOption options = LoadOption::DEFAULT
		) {
			IntrusivePointer<Task> task = makeIntrusive<Task>(path, [this, path, workingDir, format, onLoaded, onError, options] {
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
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) {
			BaseLoader* loader = getLoader(Ghurund::Core::getType<T>());
			return (T*)loadInternal(*loader, buffer, workingDir, format, options);
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
			IntrusivePointer<Task> task = makeIntrusive<Task>(path, [this, path, workingDir, format, onLoaded, onError, options] {
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
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const {
			const Loader* loader = getLoader(Ghurund::Core::getType<T>());
			Buffer buffer;
			saveInternal(resource, *loader, buffer, workingDir, format, options);
		}

		template<Derived<Resource> T>
		void save(
			T& resource,
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const {
			auto absolutePath = getAbsolutePath(path, workingDir);
			resource.Path = &absolutePath;
			const BaseLoader* loader = getLoader(Ghurund::Core::getType<T>());
			//Library* library = path.findLibrary(libraries);
			//if (library) {
				//auto buffer = path.resolveResource(workingDir, libraries);
				//saveInternal(resource, *loader, workingDir, buffer, format, options);
			//} else {
				Buffer buffer;
				saveInternal(resource, *loader, buffer, workingDir, format, options);
				File file(*resource.Path);
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

		LibraryCollection& getLibraries() {
			return libraries;
		}

		__declspec(property(get = getLibraries)) LibraryCollection& Libraries;
	};
}
