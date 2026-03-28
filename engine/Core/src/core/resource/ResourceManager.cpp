#include "ghcpch.h"
#include "ResourceManager.h"

#include "core/EnumOperators.h"
#include "core/io/File.h"
#include "core/Timer.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
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
		const WString cacheKey = getCacheKey(path, workingDir);
		auto iterator = resourceCache.find(cacheKey);
		SharedPointer<Buffer> buffer;
		if (iterator == resourceCache.end()) {
			Logger::log(LogType::INFO, std::format(_T("loading {} from resource\n"), path).c_str());
			buffer = resolveResource(path, workingDir);
			resourceCache.put(cacheKey, buffer);
		} else {
			Logger::log(LogType::INFO, std::format(_T("loading {} from cache\n"), path).c_str());
			buffer = iterator->value;
		}

		return loadInternal(loader, *buffer.get(), getLocalDir(path, workingDir), format, options);
	}

	Resource* ResourceManager::loadInternal(
		BaseLoader& loader,
		const Buffer& buffer,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		if (buffer.Size == 0) {
			auto message = std::format(_T("the buffer is empty\n"));
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidParamException(exMessage.Data);
		}
		MemoryInputStream stream(buffer.Data, buffer.Size);
		IntrusivePointer<Resource> resource;
		try {
			resource = IntrusivePointer(loader.load(stream, workingDir, format, options));
		} catch (std::exception& exception) {
			auto text = std::format(_T("failed to load resource\n"));
			Logger::log(LogType::ERR0R, text.c_str());
			throw exception;
		}

		/*if (hotReloadEnabled && !(options & LoadOption::DONT_WATCH)) {
			watcher.addFile(path, [this, &loader, &resource](const FilePath& path, const FileChange& fileChange) {
				if (fileChange == FileChange::MODIFIED) {
					section.enter();
					bool found = false;
					for (size_t i = 0; i < reloadQueue.Size; i++) {
						if (reloadQueue[i]->Resource.Path == resource.Path) {
							found = true;
							break;
						}
					}
					if (!found) {
						resource.Valid = false;
						reloadQueue.add(ghnew ReloadTask(loader, resource));
					}
					section.leave();
				}
			});
		}*/
		//if (!(options & LoadOption::DONT_CACHE))
			//resources.add(*resource);

		resource->addReference();
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
		} else {
			resource->addReference();
		}
		auto absolutePath = getAbsolutePath(path, workingDir);
		resource->Path = &absolutePath;
		if ((options & LoadOption::DONT_CACHE) != LoadOption::DONT_CACHE)
			resources.add(cacheKey, *resource);
		return resource;
	}

	const Ghurund::Core::Type& ResourceManager::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<ResourceManager>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<ResourceManager>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const DirectoryPath ResourceManager::ENGINE_LIB = DirectoryPath(std::format(L"{}{}", LIB_PROTOCOL, ENGINE_LIB_NAME).c_str());

	ResourceManager::ResourceManager() {
		loadingThread.start();
	}

	ResourceManager::~ResourceManager() {
		loadingThread.finish();
	}

	void ResourceManager::reload() {
		if (!hotReloadEnabled)
			return;

		if (!reloadQueue.Empty) {
			Timer timer;
			timer.tick();
			ticks_t startTime = timer.Ticks;
			Logger::log(LogType::INFO, _T("hot reload started\n"));
			for (size_t i = 0; i < reloadQueue.Size; i++) {
				ReloadTask* task = reloadQueue.get(i);
				task->execute();    // TODO: try to reload in place
				delete task;
			}
			timer.tick();
			ticks_t finishTime = timer.Ticks;
			float dt = (float)((double)(finishTime - startTime) * 1000 / (double)timer.Frequency);
			auto text = std::format(_T("hot reload finished in %fms\n"), dt);
			Logger::log(LogType::INFO, text.c_str());
		}
		reloadQueue.clear();
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