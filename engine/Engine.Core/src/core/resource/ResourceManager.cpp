#include "ghcpch.h"
#include "ResourceManager.h"

#include "core/Timer.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    Resource* ResourceManager::loadInternal(Loader& loader, const FilePath& path, const ResourceFormat* format, LoadOption options) {
        std::unique_ptr<File> file;
        WString pathString = WString(path.toString());
        size_t libProtocolLength = lengthOf(LIB_PROTOCOL);
        size_t fileProtocolLength = lengthOf(FILE_PROTOCOL);
        if (pathString.startsWith(LIB_PROTOCOL)) {
            pathString.replace(L'\\', L'/');
            size_t separatorIndex = pathString.find(L"/", libProtocolLength);
            if (separatorIndex == pathString.Size) {
                auto message = std::format(_T("the path '{}' has to contain '/'\n"), pathString);
                Logger::log(LogType::ERR0R, message.c_str());
                AString exMessage = convertText<tchar, char>(String(message.c_str()));
                throw InvalidParamException(exMessage.Data);
            }
            WString libName = pathString.substring(libProtocolLength, separatorIndex - libProtocolLength);
            WString fileName = pathString.substring(separatorIndex + 1);
            file.reset(libraries.get(libName)->getFile(fileName));
            if (file.get() == nullptr || file->Size == 0 && !file->Exists) {
                auto message = std::format(_T("the file '{}' in library '{}' doesn't exist\n"), fileName, libName);
                Logger::log(LogType::ERR0R, message.c_str());
                AString exMessage = convertText<tchar, char>(String(message.c_str()));
                throw InvalidParamException(exMessage.Data);
            }
        } else if (pathString.startsWith(FILE_PROTOCOL)) {
            pathString.replace(L'\\', L'/');
            WString fileName = pathString.substring(fileProtocolLength);
            file.reset(ghnew File(fileName));
            if (!file->Exists) {
                auto message = std::format(_T("the file '{}' doesn't exist\n"), fileName);
                Logger::log(LogType::ERR0R, message.c_str());
                AString exMessage = convertText<tchar, char>(String(message.c_str()));
                throw InvalidParamException(exMessage.Data);
            }
        } else {
            file.reset(ghnew File(path));
            if (!file->Exists) {
                auto message = std::format(_T("the file '{}' doesn't exist\n"), path);
                Logger::log(LogType::ERR0R, message.c_str());
                AString exMessage = convertText<tchar, char>(String(message.c_str()));
                throw InvalidParamException(exMessage.Data);
            }
        }

        if (file->Size == 0) {
            Status result = file->read();
            if (result != Status::OK) {
                auto message = std::format(_T("failed to load file '{}'\n"), file->Path);
                Logger::log(LogType::ERR0R, message.c_str());
                AString exMessage = convertText<tchar, char>(String(message.c_str()));
                throw CallFailedException(exMessage.Data);
            }
        }

        return loadInternal(loader, *file, format, options);
    }

    Resource* ResourceManager::loadInternal(Loader& loader, const File& file, const ResourceFormat* format, LoadOption options) {
        if (file.Size == 0) {
            auto message = std::format(_T("the file '{}' is empty\n"), file.Path);
            Logger::log(LogType::ERR0R, message.c_str());
            AString exMessage = convertText<tchar, char>(String(message.c_str()));
            throw InvalidParamException(exMessage.Data);
        }
        MemoryInputStream stream(file.Data, file.Size);
        Resource* resource;
        try {
            resource = loader.load(*this, stream, format, options);
        } catch (std::exception& exception) {
            auto text = std::format(_T("failed to load file: {}\n"), file.Path);
            Logger::log(LogType::ERR0R, text.c_str());
            throw exception;
        }
        resource->Path = &file.Path;

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
            add(*resource);

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
        //loadingThread.start();
    }

    ResourceManager::~ResourceManager() {
        //loadingThread.finish();
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
            auto text = std::format(_T("hot reload finished in %fms\n"), dt);
            Logger::log(LogType::INFO, text.c_str());
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