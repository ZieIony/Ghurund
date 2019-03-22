#pragma once

#include "audio/Audio.h"
#include "collection/PointerMap.h"
#include "collection/HashMap.h"
#include "core/Logger.h"
#include "core/Noncopyable.h"
#include "core/Object.h"
#include "core/WorkerThread.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/CommandList.h"
#include "resource/LibraryList.h"
#include "resource/ReloadTask.h"
#include "resource/Resource.h"
#include "resource/ResourceFactory.h"
#include "resource/watcher/FileWatcher.h"

#include <wincodec.h>

namespace Ghurund {
    class ResourceManager:public Noncopyable, public Object {
    private:
        FileWatcher watcher;
        PointerMap<String, Resource*> resources;
        LibraryList libraries;
        CriticalSection section;
        ResourceFactory* resourceFactory = ghnew DefaultResourceFactory();

        WorkerThread loadingThread;
        List<ReloadTask*> reloadQueue;
        bool hotReloadEnabled
#ifdef _DEBUG
            = true;
#else
            = false;
#endif

        Status loadInternal(Resource& resource, ResourceContext& context, const FilePath& path, LoadOption options);

        FilePath decodePath(const UnicodeString& fileName, const DirectoryPath* workingDir = nullptr) const;
        FilePath encodePath(const FilePath& resourcePath, const DirectoryPath& workingDir) const;

    public:
        static const wchar_t* const ENGINE_LIB_NAME;
        static const wchar_t* const LIB_PROTOCOL_PREFIX;

        ResourceManager();

        ~ResourceManager();

        void reload();

        template<class Type> Type* load(ResourceContext& context, const FilePath& path, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Resource* resource = get(path);
            Status loadResult = Status::ALREADY_LOADED;
            if (resource == nullptr) {
                resource = ghnew Type();
                loadResult = loadInternal(*resource, context, decodePath(path), options);
                if (filterStatus(loadResult, options) != Status::OK) {
                    resource->release();
                    resource = nullptr;
                }
            }
            if (result != nullptr)
                * result = loadResult;
            return (Type*)resource;
        }

        template<class Type> void loadAsync(ResourceContext & context, const FilePath & path, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Task* task = ghnew Task(path, [this, &context, path, onLoaded, options]() {
                Resource* resource = get(path);
                Status loadResult = Status::ALREADY_LOADED;
                if (resource == nullptr) {
                    resource = ghnew Type();
                    loadResult = loadInternal(*resource, context, decodePath(path), options);
                    if (filterStatus(loadResult, options) != Status::OK) {
                        resource->release();
                        resource = nullptr;
                    }
                }
                if (onLoaded != nullptr)
                    onLoaded((Type*)resource, loadResult);
                return loadResult;
                });
            loadingThread.post(task);
            task->release();
        }

        template<class Type> Type * load(ResourceContext & context, File & file, Status * result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Resource* resource = get(file.Path);
            Status loadResult = Status::ALREADY_LOADED;
            if (resource == nullptr) {
                resource = ghnew Type();
                loadResult = loadInternal(*resource, context, decodePath(file.Path), options);
                if (filterStatus(loadResult, options) != Status::OK) {
                    resource->release();
                    resource = nullptr;
                }
            }
            if (result != nullptr)
                * result = loadResult;
            return (Type*)resource;
        }

        template<class Type> Type* loadAsync(ResourceContext & context, File & file, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Task* task = ghnew Task(file.Path, [this, &context, file.Path, onLoaded, options]() {
                Type* resource = get<Type>(file.Path);
                Status result = Status::ALREADY_LOADED;
                if (resource == nullptr) {
                    resource = ghnew Type();
                    result = loadInternal(*resource, context, decodePath(file.Path), options);
                    if (filterStatus(loadResult, options) != Status::OK) {
                        resource->release();
                        resource = nullptr;
                    }
                }
                if (onLoaded != nullptr)
                    onLoaded(resource, result);
                return result;
            });
            loadingThread.post(task);
            task->release();
        }

        template<class Type = Resource> Type * load(ResourceContext & context, const DirectoryPath & workingDir, MemoryInputStream & stream, Status * result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Type* resource = (Type*)resourceFactory->makeResource(stream);
            Status loadResult;
            if (stream.readBoolean()) {
                loadResult = resource->load(*this, context, workingDir, stream, options);
            } else {
                loadResult = loadInternal(*resource, context, decodePath(stream.readUnicode(), &workingDir), options);
            }
            if (filterStatus(loadResult, options) != Status::OK) {
                resource->release();
                resource = nullptr;
            }
            if (result != nullptr)
                * result = loadResult;
            return resource;
        }

        Status save(Resource & resource, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource & resource, const FilePath & path, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource & resource, File & file, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource & resource, const DirectoryPath & workingDir, MemoryOutputStream & stream, SaveOption options = SaveOption::DEFAULT);

        Resource * get(const String & fileName);

        void add(Resource & resource);

        void remove(const String & fileName);

        void clear();

        void setHotReloadEnabled(bool enabled) {
            this->hotReloadEnabled = enabled;
        }

        bool isHotReloadEnabled() {
            return hotReloadEnabled;
        }

        __declspec(property(get = isHotReloadEnabled, put = setHotReloadEnabled)) bool HotReloadEnabled;

        LibraryList & getLibraries() {
            return libraries;
        }

        __declspec(property(get = getLibraries)) LibraryList & Libraries;

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}
