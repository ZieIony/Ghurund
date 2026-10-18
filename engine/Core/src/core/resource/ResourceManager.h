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

		template<typename T>
		inline const ResourceFormat& guessResourceFormat(const FilePath& path, const ResourceFormat& format) const {
			if (format != ResourceFormat::AUTO)
				return format;
			for (auto& resourceFormat : T::FORMATS) {
				if (path.Extension == resourceFormat.FileExtension)
					return resourceFormat;
			}
			return ResourceFormat::AUTO;
		}

		BaseLoader* getLoader(const Ghurund::Core::Type& type) const;

		[[nodiscard]]
		CoroutineTask<void> load_internal(
			Resource& resource,
			BaseLoader& loader,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		);

		[[nodiscard]]
		CoroutineTask<void> init_internal(Resource& resource, BaseLoader& loader);

		void save_internal(
			Resource& resource,
			const BaseLoader& loader,
			Buffer& buffer,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOptions options
		) const;

		void onResourceChanged(Resource& resource) {
			scheduler.launch(reload(resource));
		}

		inline static const WString LOAD_GENERATE_NAME_VALUE = L"";

	public:
		inline static const WString ENGINE_LIB_NAME = L"Ghurund";
		static const DirectoryPath ENGINE_LIB_PATH;
		inline static const WString LIB_PROTOCOL = L"lib://";

		static constexpr const WString* LOAD_GENERATE_NAME = &LOAD_GENERATE_NAME_VALUE;

		explicit ResourceManager(CoroutineScheduler& scheduler):scheduler(scheduler) {
			IsHotReloadEnabled = IS_DEBUG_BUILD && !IS_UNIT_TEST;
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
			} else if (path.IsLibrary) {
				return resolvePath(path).Directory;
			} else {
				return workingDir;
			}
		}

		inline void removeFromCache(
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory()
		) {
			auto absoluteOrLibPath = resolvePath(getAbsoluteOrLibPath(path, workingDir));
			resources.remove(absoluteOrLibPath);
		}

		CoroutineTask<void> reload(Resource& resource);

		/**
		* Loads a resource by name. May throw if loading the resource fails.
		* Parameter 'path' can lead to a file, or to a library entry. Parameter 'name' can be nullptr. If parameter 'name' is 'LOAD_GENERATE_NAME', then a name will be generated.
		* Default parameters are: workingDir = DirectoryPath::getCurrentDirectory(), format = ResourceFormat::AUTO, name = LOAD_GENERATE_NAME, options = {}.
		**/
		template<Derived<Resource> T>
		[[nodiscard]]
		CoroutineTask<IntrusivePointer<T>> load(
			const WString& name,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOptions options = {}
		) {
			IntrusivePointer<T> resource = IntrusivePointer<T>((T*)resources.get(name));
			if (resource == nullptr) {
				throw std::invalid_argument("resource is not present in cache");
			} else {
				resource->addReference();
			}

			BaseLoader& loader = *getLoader(Ghurund::Core::getType<T>());

			if (resource->State == ResourceState::EMPTY && options.targetState != ResourceState::EMPTY) {
				auto absoluteOrLibPath = resource->Path;
				if (!absoluteOrLibPath)
					throw InvalidStateException("resource needs a valid path to be loaded by name");

				auto& loadFormat = guessResourceFormat<T>(*absoluteOrLibPath, format);

#ifdef _DEBUG
				auto message = std::format(_T("Loading resource by name '{}'.\n"), name);
				Logger::log(LogType::INFO, message.c_str());
#endif
				SharedPointer<Buffer> buffer = resolveResource(*absoluteOrLibPath);
				MemoryInputStream stream = MemoryInputStream(buffer->Data, buffer->Size);
				auto localDir = getLocalDir(*absoluteOrLibPath, workingDir);
				co_await load_internal(resource.ref(), loader, stream, localDir, format, options);
			}

			if (options.clone)
				resource = IntrusivePointer<T>((T*)resource->clone());

			if (resource->State == ResourceState::LOADED && options.targetState != ResourceState::LOADED) {
#ifdef _DEBUG
				auto message = std::format(_T("Initializing resource by name '{}'.\n"), name);
				Logger::log(LogType::INFO, message.c_str());
#endif
				co_await init_internal(resource.ref(), loader);
			}

			co_return resource;
		}

		/**
		* Loads a resource from file path, optionally caches the resource and watches for file changes. May throw if loading the resource fails.
		* Parameter 'path' can lead to a file, or to a library entry. Parameter 'name' can be nullptr. If parameter 'name' is 'LOAD_GENERATE_NAME', then a name will be generated.
		* Default parameters are: workingDir = DirectoryPath::getCurrentDirectory(), format = ResourceFormat::AUTO, name = LOAD_GENERATE_NAME, options = {}.
		**/
		template<Derived<Resource> T>
		[[nodiscard]]
		CoroutineTask<IntrusivePointer<T>> load(
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			const WString* name = LOAD_GENERATE_NAME,
			LoadOptions options = {}
		) {
			BaseLoader& loader = *getLoader(Ghurund::Core::getType<T>());

			auto absoluteOrLibPath = resolvePath(getAbsoluteOrLibPath(path, workingDir));
			IntrusivePointer<T> resource = IntrusivePointer<T>((T*)resources.get(absoluteOrLibPath));
			if (resource == nullptr){
				auto typelessResource = loader.makeResource();
				resource = IntrusivePointer<T>((T*)typelessResource.get());
				resource->Path = &absoluteOrLibPath;
				if (name == LOAD_GENERATE_NAME) {
					resource->Name = WString(absoluteOrLibPath.FileName.Data);
				} else if (name) {
					resource->Name = name;
				}
				resources.put(resource.ref());
				if (options.watch && absoluteOrLibPath.IsAbsolute)
					watcher.addFile(absoluteOrLibPath);
			} else {
				resource->addReference();
			}

			if (resource->State == ResourceState::EMPTY && options.targetState != ResourceState::EMPTY) {
				auto& loadFormat = guessResourceFormat<T>(path, format);

#ifdef _DEBUG
				auto message = std::format(_T("Loading resource from '{}'.\n"), absoluteOrLibPath.toString());
				Logger::log(LogType::INFO, message.c_str());
#endif
				SharedPointer<Buffer> buffer = resolveResource(absoluteOrLibPath);
				MemoryInputStream stream = MemoryInputStream(buffer->Data, buffer->Size);
				auto localDir = getLocalDir(absoluteOrLibPath, workingDir);
				co_await load_internal(resource.ref(), loader, stream, localDir, format, options);
			}

			if (options.clone)
				resource = IntrusivePointer<T>((T*)resource->clone());

			if (resource->State == ResourceState::LOADED && options.targetState != ResourceState::LOADED) {
#ifdef _DEBUG
				auto message = std::format(_T("Initializing resource from '{}'.\n"), absoluteOrLibPath.toString());
				Logger::log(LogType::INFO, message.c_str());
#endif
				co_await init_internal(resource.ref(), loader);
			}

			co_return resource;
		}

		/**
		* Loads a resource from memory stream, optionally caches the resource. May throw if loading the resource fails.
		* Parameter 'name' can be nullptr.
		* Default parameters are: workingDir = DirectoryPath::getCurrentDirectory(), format = ResourceFormat::AUTO, name = LOAD_GENERATE_NAME, options = {}.
		**/
		template<Derived<Resource> T>
		[[nodiscard]]
		CoroutineTask<IntrusivePointer<T>> load(
			MemoryInputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			const WString* name = LOAD_GENERATE_NAME,
			LoadOptions options = {}
		) {
			BaseLoader& loader = *getLoader(Ghurund::Core::getType<T>());

			IntrusivePointer<T> resource;
			if (name && name != LOAD_GENERATE_NAME)
				resource = IntrusivePointer<T>((T*)resources.get(*name));
			if (resource == nullptr) {
				auto typelessResource = loader.makeResource();
				resource = IntrusivePointer<T>((T*)typelessResource.get());
				if (name)
					resource->Name = *name;
				resources.put(resource.ref());
			} else {
				resource->addReference();
			}

			if (resource->State == ResourceState::EMPTY && options.targetState != ResourceState::EMPTY) {
#ifdef _DEBUG
				Logger::log(LogType::INFO, _T("Loading resource from stream.\n"));
#endif
				co_await load_internal(resource.ref(), loader, stream, workingDir, format, options);
			}

			if (options.clone)
				resource = IntrusivePointer<T>((T*)resource->clone());

			if (resource->State == ResourceState::LOADED && options.targetState != ResourceState::LOADED) {
#ifdef _DEBUG
				auto message = std::format(_T("Initializing from stream.\n"));
				Logger::log(LogType::INFO, message.c_str());
#endif
				co_await init_internal(resource.ref(), loader);
			}

			co_return resource;
		}

		template<Derived<Resource> T>
		[[nodiscard]]
		CoroutineTask<void> init(T& resource) {
			BaseLoader& loader = getLoader(Ghurund::Core::getType<T>());
			co_await init_internal(resource, loader);
		}

		template<Derived<Resource> T>
		void save(
			T& resource,
			Buffer& buffer,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOptions options = {}
		) const {
			const Loader* loader = getLoader(T::TYPE);
			auto& saveFormat = format;
			if (resource.Path)
				saveFormat = guessResourceFormat<T>(*resource.Path, format);
			save_internal(resource, *loader, buffer, workingDir, saveFormat, options);
		}

		template<Derived<Resource> T>
		void save(
			T& resource,
			const FilePath& path,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOptions options = {}
		) const {
			auto absoluteOrLibPath = resolvePath(getAbsoluteOrLibPath(path, workingDir));
			if (absoluteOrLibPath.IsLibrary)
				throw NotSupportedException("Saving to file libraries is not supported.");
			resource.Path = &absoluteOrLibPath;
			const BaseLoader* loader = getLoader(T::TYPE);
			auto& saveFormat = guessResourceFormat<T>(path, format);
			//Library* library = path.findLibrary(libraries);
			//if (library) {
				//auto buffer = path.resolveResource(workingDir, libraries);
				//save_internal(resource, *loader, workingDir, buffer, format, options);
			//} else {
			Buffer buffer;
			save_internal(resource, *loader, buffer, workingDir, saveFormat, options);
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
	};
}
