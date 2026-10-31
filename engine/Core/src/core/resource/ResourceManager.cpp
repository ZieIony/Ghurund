#include "ghcpch.h"
#include "ResourceManager.h"

#include "core/enum/EnumOperators.h"
#include "core/io/File.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

#include "core/logging/Formatter.h"

namespace Ghurund::Core {
	FilePath ResourceManager::resolvePath(const FilePath& absoluteOrLibPath) const {
		if (absoluteOrLibPath.IsLibrary) {
			WString pathStr = absoluteOrLibPath.toString();
			size_t afterLibName = pathStr.find(Path::SEPARATOR, LIB_PROTOCOL.Size);
			const WString libName = pathStr.substring(LIB_PROTOCOL.Length, afterLibName);
			const WString relativePath = pathStr.substring(afterLibName + 1);
			const Library* library = libraries.get(libName);
			if (!library)
				throw std::invalid_argument(std::format("library \"{}\" doesn't exist", libName));
			try {
				return library->getAbsolutePath(relativePath);
			} catch (...) {
				return absoluteOrLibPath;	// file library
			}
		} else {
			return absoluteOrLibPath;
		}
	}

	SharedPointer<Buffer> ResourceManager::resolveResource(const FilePath& absoluteOrLibPath) const {
		if (absoluteOrLibPath.IsLibrary) {
			WString pathStr = absoluteOrLibPath.toString();
			size_t afterLibName = pathStr.find(Path::SEPARATOR, LIB_PROTOCOL.Size);
			const WString libName = pathStr.substring(LIB_PROTOCOL.Length, afterLibName);
			const WString relativePath = pathStr.substring(afterLibName + 1);
			const Library* library = libraries.get(libName);
			if (!library)
				throw std::invalid_argument(std::format("library \"{}\" doesn't exist", libName));
			return library->get(relativePath);
		} else {
			File file(absoluteOrLibPath);
			if (!file.Exists)
				throw std::invalid_argument(std::format("path \"{}\" doesn't exist", absoluteOrLibPath));
			auto buffer = makeShared<Buffer>();
			file.read(buffer.ref());
			return buffer;
		}
	}

	BaseLoader* ResourceManager::getLoader(const Ghurund::Core::Type& type) const {
		BaseLoader* loader = loaders.get(type);

		if (!loader) {
			auto message = std::format(_T("loader for type {} is missing\n"), type.Name);
			Logger::logAndThrow<InvalidStateException>(message.c_str());
		}

		return loader;
	}

	CoroutineTask<void> ResourceManager::load_internal(
		Resource& resource,
		BaseLoader& loader,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		try {
			co_await loader.load(resource, stream, workingDir, format, options);
			_ASSERTE(resource.State != ResourceState::EMPTY);
			_ASSERTE(resource.DataSize.system > 0);
		} catch (...) {
			auto message = std::format(_T("failed to load resource {}\n"), resource.Type.Name);
			Logger::log(LogType::ERR0R, message.c_str());
			std::exception_ptr exception = std::current_exception();
			std::rethrow_exception(exception);
		}
	}

	CoroutineTask<void> ResourceManager::init_internal(Resource& resource, BaseLoader& loader) {
		try {
			co_await loader.init(resource);
			_ASSERTE(resource.State == ResourceState::INITIALIZED);
		} catch (...) {
			auto text = std::format(_T("failed to init resource\n"));
			Logger::log(LogType::ERR0R, text.c_str());
			std::exception_ptr exception = std::current_exception();
			std::rethrow_exception(exception);
		}
	}

	void ResourceManager::save_internal(
		Resource& resource,
		const BaseLoader& loader,
		Buffer& buffer,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOptions options
	) const {
		MemoryOutputStream stream;
		try {
			loader.save(resource, stream, workingDir, format, options);
		} catch (...) {
			Logger::log(LogType::ERR0R, std::format(_T("failed to save resource\n")).c_str());
			std::exception_ptr exception = std::current_exception();
			std::rethrow_exception(exception);
		}
		buffer.setData(stream.Data, stream.BytesWritten);
	}

	const Ghurund::Core::Type& ResourceManager::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ResourceManager>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const DirectoryPath ResourceManager::ENGINE_LIB_PATH = DirectoryPath(std::format(L"{}{}", LIB_PROTOCOL, ENGINE_LIB_NAME).c_str());

	CoroutineTask<void> ResourceManager::reload(Resource& resource) {
		co_await scheduler.nextUpdate();
		co_await scheduler.backgroundThread();
		//co_await reload(resource);
		co_await scheduler.nextUpdate();
		// TODO: implement this
	}

	void ResourceManager::setIsHotReloadEnabled(bool enabled) {
		this->hotReloadEnabled = enabled;
		if (enabled) {
			watcher.fileChanged += [this](FileWatcher&, const FileChange& change) {
				if (change.Type != FileChangeType::MODIFIED) {
					// TODO: is this going to work for resources loaded using different working dirs, for example shaders loaded for materials for models?
					resources.remove(change.Path);
					watcher.removeFile(change.Path);
				} else {
					auto resource = resources.get(change.Path);
					onResourceChanged(*resource);
				}
				return true;
			};
		} else {
			watcher.fileChanged.clear();
		}
	}

	/*Status ResourceManager::save(MemoryOutputStream& stream, Resource& resource, const DirectoryPath& workingDir,const ResourceFormat* format, SaveOptions options) const {
		size_t index = Ghurund::Core::Type::TYPES.find([&](const std::reference_wrapper<const Ghurund::Core::Type> obj) { return obj.get() == resource.getType(); });
		stream.writeUInt32((uint32_t)index);
		if (resource.Path == nullptr) {
			stream.writeBoolean(true);  // full binary
			return resource.save(workingDir, stream, options);
		} else {
			stream.writeBoolean(false); // file reference
			stream.writeUnicode(resource.Path->toString().Data);
			return resource.save(*resource.Path, options);
		}
	}*/
}
