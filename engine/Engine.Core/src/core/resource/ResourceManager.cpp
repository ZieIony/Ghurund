#include "ghcpch.h"
#include "ResourceManager.h"

#include "core/Timer.h"
#include "core/logging/Formatter.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    Status ResourceManager::loadInternal(Loader& loader, Resource& resource, const FilePath& path, LoadOption options) {
        File* file;
        WString pathString = path.toString();
        size_t protocolLength = lengthOf(LIB_PROTOCOL);
        if (pathString.startsWith(LIB_PROTOCOL)) {
            WString libName = pathString.substring(protocolLength, pathString.find(L"\\", protocolLength) - protocolLength);
            WString fileName = pathString.substring(pathString.find(L"\\", protocolLength));
            file = libraries.get(libName)->getFile(fileName);
        } else {
            file = ghnew File(path);
            if (!file->Exists) {
                delete file;
                return Status::FILE_DOESNT_EXIST;
            }
        }

        file->read();
        MemoryInputStream stream(file->Data, file->Size);
        resource.Path = &path;
        Status result = loader.load(*this, stream, resource, options);
        delete file;
        if (result != Status::OK)
            return Logger::log(LogType::ERR0R, result, _T("failed to load file: {}\n"), path);

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
        add(resource);

        return Status::OK;
    }

    const Ghurund::Type& ResourceManager::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<ResourceManager>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ResourceManager))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    ResourceManager::ResourceManager() {
        loadingThread.start();
    }

    ResourceManager::~ResourceManager() {
        for (size_t i = 0; i < loaders.Size; i++) {
            Loader* loader = loaders.getValue(i);
            loaders.remove(loaders.getKey(i));
            delete loader;
        }
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

    Status ResourceManager::save(Resource& resource, SaveOption options) {
        return resource.save(options);
    }

    Status ResourceManager::save(Resource& resource, const FilePath& path, SaveOption options) {
        return resource.save(path, options);
    }

    Status ResourceManager::save(Resource& resource, File& file, SaveOption options) {
        return resource.save(file, options);
    }

    Status ResourceManager::save(Resource& resource, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) {
        size_t index = Ghurund::Type::TYPES.indexOf(resource.getType());
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