#include "ResourceManager.h"
#include <functional>
#include "TextResource.h"

namespace Ghurund {
    Status ResourceManager::loadInternal(Resource& resource, ResourceContext& context, const FilePath& path, LoadOption options) {
        Status result = resource.load(*this, context, path, nullptr, options);
        if (result != Status::OK) {
            Logger::log(_T("failed to load file: %s\n"), path.get().getData());
            return result;
        }

        if (hotReloadEnabled && !(options& LoadOption::DONT_WATCH)) {
            watcher.addFile(path, [this, &resource, &context](const FilePath & path, FileChange fileChange) {
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
                        reloadQueue.add(ghnew ReloadTask(*this, context, resource));
                    }
                    section.leave();
                }
                });
        }
        add(resource);

        return Status::OK;
    }

    ResourceManager::ResourceManager() {
        loadingThread.start();
    }

    ResourceManager::~ResourceManager() {
        loadingThread.finish();
        delete resourceFactory;
    }

    void ResourceManager::reload() {
        section.enter();
        for (size_t i = 0; i < reloadQueue.Size; i++) {
            ReloadTask* task = reloadQueue.get(i);
            task->execute();    // TODO: try to reload in place
            delete task;
        }
        reloadQueue.clear();
        section.leave();
    }

    Status ResourceManager::save(Resource& resource, SaveOption options) {
        return resource.save(*this, options);
    }

    Status ResourceManager::save(Resource& resource, const FilePath& path, SaveOption options) {
        return resource.save(*this, path, options);
    }

    Status ResourceManager::save(Resource& resource, File& file, SaveOption options) {
        return resource.save(*this, file, options);
    }

    Status ResourceManager::save(Resource& resource, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) {
        resourceFactory->describeResource(resource, stream);
        if (resource.Path == nullptr) {
            stream.writeBoolean(true);  // full binary
            return resource.save(*this, workingDir, stream, options);
        } else {
            stream.writeBoolean(false); // file reference
            FilePath relativePath = resource.Path->getRelativePath(workingDir);
            if (relativePath == *resource.Path) {
                size_t libIndex = libraries.findFile(*resource.Path);
                if (libIndex != libraries.Size) {
                    UnicodeString libPathString = L"lib:";
                    libPathString.add(libraries.get(libIndex).Name);
                    libPathString.add("\\");
                    libPathString.add(libraries.get(libIndex).Path);
                    stream.writeUnicode(libPathString);
                } else {
                    Logger::log(_T("Saving resource by absolute path reference (%s)\n"), String(resource.Path->get()).getData());
                    stream.writeUnicode(*resource.Path);
                }
            } else {
                stream.writeUnicode(resource.Path->getRelativePath(workingDir));
            }
            Status result = resource.save(*this, *resource.Path, options);
            if (options& SaveOption::SKIP_IF_EXISTS&& result == Status::FILE_EXISTS)
                return Status::OK;
            return result;
        }
    }

    Resource* ResourceManager::get(const String & fileName) {
        section.enter();
        Resource* resource = nullptr;
        size_t index = resources.findKey(fileName);
        if (index != resources.Size)
            resource = resources.getValue(index);
        section.leave();
        return resource;
    }

    void ResourceManager::add(Resource & resource) {
        section.enter();
        resources.set(*resource.Path, &resource);
        section.leave();
    }

    void ResourceManager::remove(const String & fileName) {
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