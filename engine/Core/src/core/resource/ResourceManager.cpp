#include "ghcpch.h"
#include "ResourceManager.h"

#include "core/EnumOperators.h"
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
			// this throws if library is not a DirectoryLibrary
			return library->getAbsolutePath(relativePath);
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
			Logger::log(LogType::ERR0R, message.c_str());
			auto exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidStateException(exMessage.Data);
		}

		return loader;
	}

	CoroutineTask<IntrusivePointer<Resource>> ResourceManager::loadInternal(
		BaseLoader& loader,
		const FilePath& path,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		const WString* name,
		LoadOptions options
	) {
		auto absoluteOrLibPath = getAbsoluteOrLibPath(path, workingDir);
		IntrusivePointer<Resource> resource = IntrusivePointer(resources.get(absoluteOrLibPath));
		if (resource == nullptr) {
			SharedPointer<Buffer> buffer = resolveResource(absoluteOrLibPath);
			MemoryInputStream stream = MemoryInputStream(buffer->Data, buffer->Size);
			auto localDir = getLocalDir(absoluteOrLibPath, workingDir);
			resource = co_await loadInternal(loader, stream, localDir, format, options);
			resource->Path = &absoluteOrLibPath;
			resource->Name = name ? *name : WString(absoluteOrLibPath.FileName.Data);
			if (options.cache)
				resources.put(resource.ref());
			try {
				if (options.watch && absoluteOrLibPath.IsAbsolute)
					watcher.addFile(absoluteOrLibPath);
			} catch (...) {}
		} else {
			resource->addReference();
		}
		co_return resource;
	}

	CoroutineTask<IntrusivePointer<Resource>> ResourceManager::loadInternal(
		BaseLoader& loader,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		const WString* name,
		LoadOptions options
	) {
		auto resource = co_await loadInternal(loader, stream, workingDir, format, options);
		if (name)
			resource->Name = name;
		if (options.cache)
			resources.put(resource.ref());
		co_return resource;
	}

	CoroutineTask<IntrusivePointer<Resource>> ResourceManager::loadInternal(
		BaseLoader& loader,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		IntrusivePointer<Resource> resource;
		try {
			resource = co_await loader.load(stream, workingDir, format, options);
		} catch (std::exception& exception) {
			auto text = std::format(_T("failed to load resource\n"));
			Logger::log(LogType::ERR0R, text.c_str());
			throw exception;
		}

		co_return resource;
	}

	void ResourceManager::saveInternal(
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
		} catch (std::exception& exception) {
			Logger::log(LogType::ERR0R, std::format(_T("failed to save resource\n")).c_str());
			throw exception;
		}
		buffer.setData(stream.Data, stream.BytesWritten);
	}

	CoroutineTask<void> ResourceManager::reloadResource(Resource& resource) {
		co_await scheduler.nextUpdate();
		resource.invalidate();
		co_await scheduler.backgroundThread();
		co_await reload(resource);
		co_await scheduler.nextUpdate();
		resource.validate();
	}

	const Ghurund::Core::Type& ResourceManager::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ResourceManager>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const DirectoryPath ResourceManager::ENGINE_LIB_PATH = DirectoryPath(std::format(L"{}{}", LIB_PROTOCOL, ENGINE_LIB_NAME).c_str());

	CoroutineTask<void> ResourceManager::reload(Resource& resource) {
		auto path = *resource.Path;
		auto loader = getLoader(resource.Type);
		SharedPointer<Buffer> buffer = resolveResource(path);
		MemoryInputStream stream(buffer->Data, buffer->Size);
		try {
			auto workingDir = DirectoryPath::getCurrentDirectory();
			co_await loader->load(resource, stream, getLocalDir(path, workingDir), ResourceFormat::AUTO);
		} catch (std::exception& exception) {
			auto text = std::format(_T("failed to reload resource `{}`\n"), resource.toString());
			Logger::log(LogType::ERR0R, text.c_str());
			throw exception;
		}
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

#ifdef _DEBUG
	void ResourceManager::printResources() {
		resources.printResources();
	}
#endif
}