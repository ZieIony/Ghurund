#include "ResourceManager.h"

#include "core/logging/Logger.h"

#include <functional>

namespace Ghurund {
    Status ResourceManager::loadInternal(Resource& resource, ResourceContext& context, const FilePath& path, LoadOption options) {
        Status result = resource.load(context, path, nullptr, options);
        if (result != Status::OK)
            return Logger::log(LogType::ERR0R, result, _T("failed to load file: {}\n"), path);

        if (hotReloadEnabled && !(options & LoadOption::DONT_WATCH)) {
            watcher.addFile(path, [this, &resource, &context](const FilePath& path, const FileChange& fileChange) {
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
                        reloadQueue.add(ghnew ReloadTask(context, resource));
                    }
                    section.leave();
                }
                });
        }
        add(resource);

        return Status::OK;
    }

    FilePath ResourceManager::decodePath(const WString& fileName, const DirectoryPath* workingDir) const {
        if (fileName.startsWith(LIB_PROTOCOL_PREFIX)) {
            WString libName = fileName.substring(lengthOf(LIB_PROTOCOL_PREFIX), fileName.find(L"\\", lengthOf(LIB_PROTOCOL_PREFIX)) - lengthOf(LIB_PROTOCOL_PREFIX));
            FilePath libPath(libraries.get(libName)->Path, fileName.substring(lengthOf(LIB_PROTOCOL_PREFIX) + 1 + libName.Length));
            return libPath.AbsolutePath;
        } else if (workingDir) {
            return FilePath(*workingDir, fileName).AbsolutePath;
        } else {
            return fileName;
        }
    }

    FilePath ResourceManager::encodePath(const FilePath& resourcePath, const DirectoryPath& workingDir) const {
        FilePath relativePath = resourcePath.getRelativePath(workingDir);
        if (relativePath.get().startsWith(L"..")) {
            size_t libIndex = libraries.findFile(resourcePath);
            if (libIndex != libraries.Size) {
                WString libPathString = LIB_PROTOCOL_PREFIX;
                libPathString.add(libraries.get(libIndex).Name);
                libPathString.add(L"\\");
                libPathString.add(resourcePath.getRelativePath(libraries.get(libIndex).Path));
                return libPathString;
            } else {
                if (relativePath == resourcePath)
                    Logger::log(LogType::WARNING, _T("Resource path is absolute: %s\n"), resourcePath);
                return resourcePath;
            }
        } else {
            return relativePath;
        }
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

    Status ResourceManager::save(Resource& resource, ResourceContext& context, SaveOption options) {
        return resource.save(context, options);
    }

    Status ResourceManager::save(Resource& resource, ResourceContext& context, const FilePath& path, SaveOption options) {
        return resource.save(context, path, options);
    }

    Status ResourceManager::save(Resource& resource, ResourceContext& context, File& file, SaveOption options) {
        return resource.save(context, file, options);
    }

    Status ResourceManager::save(Resource& resource, ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) {
		size_t index = Ghurund::Type::TYPES.indexOf(resource.getType());
		stream.writeUInt((uint32_t)index);
        if (resource.Path == nullptr) {
            stream.writeBoolean(true);  // full binary
            return resource.save(context, workingDir, stream, options);
        } else {
            stream.writeBoolean(false); // file reference
            stream.writeUnicode(encodePath(*resource.Path, workingDir));
            return resource.save(context, *resource.Path, options);
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