#include "ghcpch.h"
#include "ResourceManager.h"

#include "core/EnumOperators.h"
#include "core/io/File.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
	FilePath ResourceManager::resolvePath(const FilePath& path, const DirectoryPath& workingDir) const {
		FilePath absolutePath = getAbsolutePath(path, workingDir);
		WString pathStr = absolutePath.toString();
		if (pathStr.startsWith(LIB_PROTOCOL)) {
			size_t afterLibName = pathStr.find(Path::SEPARATOR, LIB_PROTOCOL.Size);
			const WString libName = pathStr.substring(LIB_PROTOCOL.Length, afterLibName);
			const WString relativePath = pathStr.substring(afterLibName + 1);
			const Library* library = libraries.get(libName);
			if (!library)
				throw InvalidParamException();
			return library->getAbsolutePath(relativePath);
		} else {
			return absolutePath;
		}
	}

	SharedPointer<Buffer> ResourceManager::resolveResource(const FilePath& path, const DirectoryPath& workingDir) const {
		FilePath absolutePath = getAbsolutePath(path, workingDir);
		WString pathStr = absolutePath.toString();
		if (pathStr.startsWith(LIB_PROTOCOL)) {
			size_t afterLibName = pathStr.find(Path::SEPARATOR, LIB_PROTOCOL.Size);
			const WString libName = pathStr.substring(LIB_PROTOCOL.Length, afterLibName);
			const WString relativePath = pathStr.substring(afterLibName + 1);
			const Library* library = libraries.get(libName);
			return library->get(relativePath);
		} else {
			File file(absolutePath);
			if (!file.Exists)
				throw InvalidParamException();
			auto buffer = SharedPointer(ghnew Buffer());
			file.read(*buffer.get());
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

	Resource* ResourceManager::loadInternal(
		BaseLoader& loader,
		const FilePath& path,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		SharedPointer<Buffer> buffer = resolveResource(path, workingDir);
		return loadInternal(loader, *buffer.get(), getLocalDir(path, workingDir), format, options);
	}

	Resource* ResourceManager::loadInternal(
		BaseLoader& loader,
		const Buffer& buffer,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		MemoryInputStream stream(buffer.Data, buffer.Size);
		IntrusivePointer<Resource> resource;
		try {
			resource = IntrusivePointer(loader.load(stream, workingDir, format, options));
		} catch (std::exception& exception) {
			auto text = std::format(_T("failed to load resource\n"));
			Logger::log(LogType::ERR0R, text.c_str());
			throw exception;
		}

		resource->addReference();
		resource->validate();
		return resource.get();
	}

	void ResourceManager::saveInternal(
		Resource& resource,
		const BaseLoader& loader,
		Buffer& buffer,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOption options
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

	CoroutineTask ResourceManager::reloadResource(Resource& resource) {
		co_await scheduler.nextUpdate();
		resource.invalidate();
		co_await scheduler.backgroundThread();
		reload(resource);
		co_await scheduler.nextUpdate();
		resource.validate();
	}

	Resource* ResourceManager::load(
		BaseLoader& loader,
		const FilePath& path,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		const WString cacheKey = getCacheKey(path, workingDir);
		Resource* resource = resources.get(cacheKey);
		if (!resource) {
			resource = loadInternal(loader, path, workingDir, format, options);
			auto absolutePath = getAbsolutePath(path, workingDir);
			resource->Path = &absolutePath;
			if ((options & LoadOption::DONT_CACHE) != LoadOption::DONT_CACHE)
				resources.add(cacheKey, *resource);
			try {
				if ((options & LoadOption::DONT_WATCH) != LoadOption::DONT_WATCH)
					watcher.addFile(resolvePath(path, workingDir));
			} catch (...) {}
		} else {
			resource->addReference();
		}
		return resource;
	}

	const Ghurund::Core::Type& ResourceManager::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ResourceManager>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const DirectoryPath ResourceManager::ENGINE_LIB = DirectoryPath(std::format(L"{}{}", LIB_PROTOCOL, ENGINE_LIB_NAME).c_str());

	void ResourceManager::reload(Resource& resource) {
		auto path = *resource.Path;
		auto workingDir = DirectoryPath();
		auto loader = getLoader(resource.Type);
		SharedPointer<Buffer> buffer = resolveResource(path, workingDir);
		MemoryInputStream stream(buffer->Data, buffer->Size);
		try {
			loader->load(resource, stream, getLocalDir(path, workingDir), ResourceFormat::AUTO);
		} catch (std::exception& exception) {
			auto text = std::format(_T("failed to reload resource `{}`\n"), resource.toString());
			Logger::log(LogType::ERR0R, text.c_str());
			throw exception;
		}
	}

	void ResourceManager::setHotReloadEnabled(bool enabled) {
		this->hotReloadEnabled = enabled;
		if (enabled) {
			watcher.fileChanged += [this](FileWatcher&, const FileChange& change)->bool {
				if (change.Type != FileChangeType::MODIFIED) {
					resources.remove(change.Path.toString());
					watcher.removeFile(change.Path);
					return true;
				}
				auto resource = IntrusivePointer(resources.get(change.Path.toString()));
				resource->addReference();
				onResourceChanged(resource.ref());
				return true;
			};
		} else {
			watcher.fileChanged.clear();
		}
	}

	/*Status ResourceManager::save(MemoryOutputStream& stream, Resource& resource, const DirectoryPath& workingDir,const ResourceFormat* format, SaveOption options) const {
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