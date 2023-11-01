#include "ghcpch.h"
#include "ResourceManager.h"

#include "core/Timer.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
	Loader* ResourceManager::getLoader(const Ghurund::Core::Type& type) const {
		Loader* loader = loaders.get(type);

		if (!loader) {
			auto message = std::format(_T("loader for type {} is missing\n"), type.Name);
			Logger::log(LogType::ERR0R, message.c_str());
			auto exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidStateException(exMessage.Data);
		}

		return loader;
	}

	Resource* ResourceManager::loadInternal(Loader& loader, const DirectoryPath& workingDir, const ResourcePath& path, const ResourceFormat* format, LoadOption options) {
		auto iterator = resourceCache.find(path);
		std::shared_ptr<Buffer> buffer;
		if (iterator == resourceCache.end()) {
			buffer = path.resolveResource(workingDir, libraries);
			resourceCache.put(path, buffer);
		} else {
			buffer = iterator->value;
		}
		return loadInternal(loader, workingDir, *buffer.get(), format, options);
	}

	Resource* ResourceManager::loadInternal(Loader& loader, const DirectoryPath& workingDir, const Buffer& buffer, const ResourceFormat* format, LoadOption options) {
		if (buffer.Size == 0) {
			auto message = std::format(_T("the buffer is empty\n"));
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidParamException(exMessage.Data);
		}
		MemoryInputStream stream(buffer.Data, buffer.Size);
		Resource* resource;
		try {
			resource = loader.load(*this, stream, workingDir, format, options);
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

		return resource;
	}

	void ResourceManager::saveInternal(Resource& resource, const Loader& loader, const DirectoryPath& workingDir, Buffer& buffer, const ResourceFormat* format, SaveOption options) const {
		MemoryOutputStream stream;
		try {
			loader.save(*this, stream, workingDir, resource, format, options);
		} catch (std::exception& exception) {
			Logger::log(LogType::ERR0R, std::format(_T("failed to save resource\n")).c_str());
			throw exception;
		}
		buffer.setData(stream.Data, stream.BytesWritten);
	}

	Resource* ResourceManager::load(Loader& loader, const File& file, const ResourceFormat* format, LoadOption options) {
		Resource* resource = resources.get(file.Path);
		if (!resource) {
			resource = loadInternal(loader, file.Path.Directory, file.Path, format, options);
		} else {
			resource->addReference();
		}
		ResourcePath filePath = file.Path;
		resource->Path = &filePath;
		if (!(options & LoadOption::DONT_CACHE))
			resources.add(file.Path, *resource);
		return resource;
	}

	Resource* ResourceManager::load(Loader& loader, const ResourcePath& path, const DirectoryPath& workingDir, const ResourceFormat* format, LoadOption options) {
		ResourcePath resolvedPath = path.getAbsolutePath(workingDir, libraries);
		Resource* resource = resources.get(resolvedPath); // TODO: why it doesn't find fonts?
		if (!resource) {
			resource = loadInternal(loader, workingDir, path, format, options);
		} else {
			resource->addReference();
		}
		resource->Path = &path;	// use the original path in case anything changes in libs
		if (!(options & LoadOption::DONT_CACHE))
			resources.add(resolvedPath, *resource);
		return resource;
	}

	const Ghurund::Core::Type& ResourceManager::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<ResourceManager>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<ResourceManager>(NAMESPACE_NAME, GH_STRINGIFY(ResourceManager))
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

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

	/*Status ResourceManager::save(Resource& resource, const DirectoryPath& workingDir, MemoryOutputStream& stream, const ResourceFormat* format, SaveOption options) const {
		size_t index = Ghurund::Core::Type::TYPES.find([&](const std::reference_wrapper<const Ghurund::Core::Type> obj) { return obj.get() == resource.getType(); });
		stream.writeUInt((uint32_t)index);
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