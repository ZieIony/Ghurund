#pragma once

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
#include <core/coroutine/CoroutineScheduler.h>


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
		ResourceCollection resources;
		LibraryCollection libraries;
		LoaderCollection loaders;

		CoroutineScheduler& scheduler;
		FileWatcher watcher;
		bool hotReloadEnabled = false;

		inline WString getCacheKey(const FilePath& path, const DirectoryPath& workingDir) const {
			try {
				return resolvePath(path, workingDir).toString();
			} catch (...) {
				return getAbsolutePath(path, workingDir).toString();
			}
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

		void onResourceChanged(Resource& resource) {
			scheduler.launch(reloadResource(resource));
		}

		CoroutineTask reloadResource(Resource& resource);

	public:
		inline static const WString ENGINE_LIB_NAME = L"Ghurund";
		static const DirectoryPath ENGINE_LIB;
		inline static const WString LIB_PROTOCOL = L"lib://";

		ResourceManager(CoroutineScheduler& scheduler):scheduler(scheduler) {
			HotReloadEnabled
#ifdef _DEBUG
			= true;
#else
			= false;
#endif
		}

		FilePath resolvePath(const FilePath& path, const DirectoryPath& workingDir) const;

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
		}

		inline void removeFromCache(Resource* resource, DirectoryPath workingDir) {
			const FilePath* path = resource->Path;
			if (path) {
				const WString cacheKey = getCacheKey(*path, workingDir);
				resources.remove(cacheKey);
			}
		}

		void reload(Resource& resource);

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

		void setHotReloadEnabled(bool enabled);

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
