#include "ResourceManager.h"
#include <functional>
#include "TextResource.h"

namespace Ghurund {
    const wchar_t* const ResourceManager::ENGINE_LIB_NAME = L"engine";
    const wchar_t* const ResourceManager::LIB_PROTOCOL_PREFIX = L"lib:\\";
    const Ghurund::Type& ResourceManager::TYPE = Ghurund::Type([]() {return ghnew ResourceManager(); }, "ResourceManager");

    Status ResourceManager::loadInternal(Resource& resource, ResourceContext& context, const FilePath& path, LoadOption options) {
        Status result = resource.load(*this, context, path, nullptr, options);
        if (result != Status::OK)
            return Logger::log(LogType::ERR0R, result, _T("failed to load file: %s\n"), path.get().getData());

        if (hotReloadEnabled && !(options & LoadOption::DONT_WATCH)) {
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

    FilePath ResourceManager::decodePath(const UnicodeString& fileName, const DirectoryPath* workingDir) const {
        if (fileName.startsWith(LIB_PROTOCOL_PREFIX)) {
            UnicodeString libName = fileName.subString(lengthOf(LIB_PROTOCOL_PREFIX), fileName.find(L"\\", lengthOf(LIB_PROTOCOL_PREFIX)) - lengthOf(LIB_PROTOCOL_PREFIX));
            FilePath libPath(libraries.get(libName)->Path, fileName.subString(lengthOf(LIB_PROTOCOL_PREFIX) + 1 + libName.Length));
            return libPath;
        } else if (workingDir) {
            return FilePath(*workingDir, fileName);
        } else {
            return fileName;
        }
    }

    FilePath ResourceManager::encodePath(const FilePath & resourcePath, const DirectoryPath & workingDir) const {
        FilePath relativePath = resourcePath.getRelativePath(workingDir);
        if (relativePath.get().startsWith(_T(".."))) {
            size_t libIndex = libraries.findFile(resourcePath);
            if (libIndex != libraries.Size) {
                UnicodeString libPathString = LIB_PROTOCOL_PREFIX;
                libPathString.add(libraries.get(libIndex).Name);
                libPathString.add("\\");
                libPathString.add(resourcePath.getRelativePath(libraries.get(libIndex).Path));
                return libPathString;
            } else {
                if (relativePath == resourcePath)
                    Logger::log(LogType::WARNING, _T("Resource path is absolute: %s\n"), String(resourcePath.get()).getData());
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

    Status ResourceManager::save(Resource & resource, SaveOption options) {
        return resource.save(*this, options);
    }

    Status ResourceManager::save(Resource & resource, const FilePath & path, SaveOption options) {
        return resource.save(*this, path, options);
    }

    Status ResourceManager::save(Resource & resource, File & file, SaveOption options) {
        return resource.save(*this, file, options);
    }

    Status ResourceManager::save(Resource & resource, const DirectoryPath & workingDir, MemoryOutputStream & stream, SaveOption options) {
        resourceFactory->describeResource(resource, stream);
        if (resource.Path == nullptr) {
            stream.writeBoolean(true);  // full binary
            return resource.save(*this, workingDir, stream, options);
        } else {
            stream.writeBoolean(false); // file reference
            stream.writeUnicode(encodePath(*resource.Path, workingDir));
            return resource.save(*this, *resource.Path, options);
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