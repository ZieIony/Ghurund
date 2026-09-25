#pragma once

#include "Resource.h"
#include "ResourceAwaiter.h"
#include "ResourceCollection.h"
#include "ResourceFormat.h"

#include "core/Buffer.h"
#include "core/coroutine/CoroutineScheduler.h"
#include "core/io/File.h"
#include "core/io/FilePath.h"
#include "core/io/LibraryCollection.h"
#include "core/io/MemoryInputStream.h"
#include "core/io/watcher/FileWatcher.h"
#include "core/loading/Loader.h"
#include "core/loading/LoaderCollection.h"
#include "core/object/Noncopyable.h"
#include "core/object/Object.h"
#include "core/reflection/Type.h"

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
		Bag<ResourceAwaiter> resourceAwaiters;
		FileWatcher watcher;
		bool hotReloadEnabled = false;

		BaseLoader* getLoader(const Ghurund::Core::Type& type) const;

		[[nodiscard]]
		CoroutineTask<IntrusivePointer<Resource>> loadInternal(
			BaseLoader& loader,
			const FilePath& path,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			const WString* name,
			LoadOptions options
		);

		[[nodiscard]]
		CoroutineTask<IntrusivePointer<Resource>> loadInternal(
			BaseLoader& loader,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			const WString* name,
			LoadOptions options
		);

		[[nodiscard]]
		CoroutineTask<IntrusivePointer<Resource>> loadInternal(
			BaseLoader& loader,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		);

		void saveInternal(
			Resource& resource,
			const BaseLoader& loader,
			Buffer& buffer,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOptions options
		) const;

		void onResourceChanged(Resource& resource) {
			scheduler.launch(reloadResource(resource));
		}

		[[nodiscard]]
		CoroutineTask<void> reloadResource(Resource& resource);

	public:
		inline static const WString ENGINE_LIB_NAME = L"Ghurund";
		static const DirectoryPath ENGINE_LIB_PATH;
		inline static const WString LIB_PROTOCOL = L"lib://";

		explicit ResourceManager(CoroutineScheduler& scheduler):scheduler(scheduler) {
			IsHotReloadEnabled =
#ifdef _DEBUG
			true;
#else
			false;
#endif
		}

		FilePath resolvePath(const FilePath& absoluteOrLibPath) const;

		SharedPointer<Buffer> resolveResource(const FilePath& absoluteOrLibPath) const;

		static inline FilePath getAbsoluteOrLibPath(const FilePath& path, const DirectoryPath& workingDir) {
			if (path.IsAbsolute || path.IsLibrary) {
				return path;
			} else if (workingDir.IsAbsolute || workingDir.IsLibrary) {
				return workingDir / path;
			} else {
				return workingDir.AbsolutePath / path;
			}
		}

		inline DirectoryPath getLocalDir(const FilePath& path, const DirectoryPath& workingDir) {
			if (path.IsAbsolute) {
				return path.Directory;
			}else if(path.IsLibrary){
				return resolvePath(path).Directory;
			} else {
				return workingDir;
			}
		}

		inline void removeFromCache(
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory()
		) {
			auto absolutePath = getAbsoluteOrLibPath(path, workingDir);
			resources.remove(absolutePath);
		}

		template<Derived<Resource> T>
		[[nodiscard]]
		IntrusivePointer<T> get(const WString& name) {
			Resource* resource = resources.get(name);
			if (resource)
				resource->addReference();
			return IntrusivePointer<T>((T*)resource);
		}

		template<Derived<Resource> T>
		[[nodiscard]]
		IntrusivePointer<T> get(
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory()
		) {
			auto cachePath = getAbsoluteOrLibPath(path, workingDir);
			Resource* resource = resources.get(cachePath);
			if (resource)
				resource->addReference();
			return IntrusivePointer<T>((T*)resource);
		}

		CoroutineTask<void> reload(Resource& resource);

		template<Derived<Resource> T>
		[[nodiscard]]
		CoroutineTask<IntrusivePointer<T>> load(
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			const WString* name = nullptr,
			LoadOptions options = {}
		) {
			BaseLoader* loader = getLoader(Ghurund::Core::getType<T>());
			IntrusivePointer<Resource> resource = co_await loadInternal(*loader, path, workingDir, format, name, options);
			resource->addReference();
			co_return IntrusivePointer<T>((T*)resource.get());
		}

		template<Derived<Resource> T>
		[[nodiscard]]
		CoroutineTask<IntrusivePointer<T>> load(
			MemoryInputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			const WString* name = nullptr,
			LoadOptions options = {}
		) {
			BaseLoader* loader = getLoader(Ghurund::Core::getType<T>());
			IntrusivePointer<Resource> resource = co_await loadInternal(*loader, stream, workingDir, format, name, options);
			resource->addReference();
			co_return IntrusivePointer<T>((T*)resource.get());
		}

		template<Derived<Resource> T>
		void save(
			T& resource,
			Buffer& buffer,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOptions options = {}
		) const {
			const Loader* loader = getLoader(Ghurund::Core::getType<T>());
			saveInternal(resource, *loader, buffer, workingDir, format, options);
		}

		template<Derived<Resource> T>
		void save(
			T& resource,
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOptions options = {}
		) const {
			auto absolutePath = getAbsoluteOrLibPath(path, workingDir);
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

		inline ResourceCollection& getResources() {
			return resources;
		}

		__declspec(property(get = getResources)) ResourceCollection& Resources;

		inline LoaderCollection& getLoaders() {
			return loaders;
		}

		__declspec(property(get = getLoaders)) LoaderCollection& Loaders;

		LibraryCollection& getLibraries() {
			return libraries;
		}

		__declspec(property(get = getLibraries)) LibraryCollection& Libraries;

		void setIsHotReloadEnabled(bool enabled);

		inline bool getIsHotReloadEnabled() const {
			return hotReloadEnabled;
		}

		__declspec(property(get = getIsHotReloadEnabled, put = setIsHotReloadEnabled)) bool IsHotReloadEnabled;

#ifdef _DEBUG
		void printResources();
#endif
	};
}
