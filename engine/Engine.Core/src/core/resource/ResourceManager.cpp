#include "ghcpch.h"
#include "ResourceManager.h"

#include "core/Timer.h"
#include "core/logging/Formatter.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    Status ResourceManager::loadInternal(Loader& loader, Resource& resource, const FilePath& path, const ResourceFormat* format, LoadOption options) {
        std::unique_ptr<File> file;
        WString pathString = WString(path.toString());
        size_t protocolLength = lengthOf(LIB_PROTOCOL);
        if (pathString.startsWith(LIB_PROTOCOL)) {
            pathString.replace(L'\\', L'/');
            size_t separatorIndex = pathString.find(L"/", protocolLength);
            if (separatorIndex == pathString.Size)
                return Status::INV_PATH;
            WString libName = pathString.substring(protocolLength, separatorIndex - protocolLength);
            WString fileName = pathString.substring(separatorIndex + 1);
            file.reset(libraries.get(libName)->getFile(fileName));
        } else {
            file.reset(ghnew File(path));
            if (!file->Exists)
                return Status::FILE_DOESNT_EXIST;
        }

        Status result = file->read();
        if (result != Status::OK)
            return Logger::log(LogType::ERR0R, result, _T("failed to load file: {}\n"), path);

        return loadInternal(loader, resource, *file, format, options);
    }

    Status ResourceManager::loadInternal(Loader& loader, Resource& resource, const File& file, const ResourceFormat* format, LoadOption options) {
        if (file.Size == 0)
            return Logger::log(LogType::ERR0R, Status::FILE_EMPTY, _T("file is empty: {}\n"), file.Path);
        MemoryInputStream stream(file.Data, file.Size);
        resource.Path = &file.Path;
        Status result = loadInternal(loader, resource, stream, format, options);
        if (result != Status::OK)
            return result;

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
        if (!(options & LoadOption::DONT_CACHE))
            add(resource);

        return Status::OK;
    }

    Status ResourceManager::loadInternal(Loader& loader, Resource& resource, MemoryInputStream& stream, const ResourceFormat* format, LoadOption options) {
        if (!format) {
            for (ResourceFormat& f : resource.Formats) {
                if (f.Extension == resource.Path->Extension && f.canLoad()) {
                    format = &f;
                    break;
                }
            }
        }
        Status result = loader.load(*this, stream, resource, format, options);
        if (result != Status::OK)
            return Logger::log(LogType::ERR0R, result, _T("failed to load file: {}\n"), *resource.Path);

        return Status::OK;
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

        section.enter();
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
            Logger::log(LogType::INFO, _T("hot reload finished in %fms\n"), dt);
        }
        reloadQueue.clear();
        section.leave();
    }

    Status ResourceManager::save(Resource& resource, const ResourceFormat* format, SaveOption options) const {
        return resource.save(options);
    }

    Status ResourceManager::save(Resource& resource, const FilePath& path, const ResourceFormat* format, SaveOption options) const {
        return resource.save(path, options);
    }

    Status ResourceManager::save(Resource& resource, File& file, const ResourceFormat* format, SaveOption options) const {
        return resource.save(file, options);
    }

    Status ResourceManager::save(Resource& resource, const DirectoryPath& workingDir, MemoryOutputStream& stream, const ResourceFormat* format, SaveOption options) const {
        size_t index = Ghurund::Core::Type::TYPES.indexOf(resource.getType());
        stream.writeUInt((uint32_t)index);
        if (resource.Path == nullptr) {
            stream.writeBoolean(true);  // full binary
            return resource.save(workingDir, stream, options);
        } else {
            stream.writeBoolean(false); // file reference
            stream.writeUnicode(resource.Path->toString().Data);
            return resource.save(*resource.Path, options);
        }
    }

    void ResourceManager::add(Resource& resource) {
        section.enter();
        resource.addReference();
        resources.set(*resource.Path, &resource);
        section.leave();
    }

    void ResourceManager::remove(const WString& fileName) {
        section.enter();
        resources.remove(fileName);
        section.leave();
    }

    void ResourceManager::clear() {
        section.enter();
        resources.clear();
        section.leave();
    }
}