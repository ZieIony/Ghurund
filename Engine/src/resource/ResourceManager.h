#pragma once

#include "core/Noncopyable.h"
#include "collection/PointerMap.h"
#include "resource/watcher/FileWatcher.h"
#include "core/Logger.h"
#include "Resource.h"
#include "core/WorkerThread.h"
#include "graphics/CommandList.h"
#include "game/ParameterManager.h"
#include "ResourceFactory.h"
#include "audio/Audio.h"
#include "ReloadTask.h"

#include <wincodec.h>

namespace Ghurund {
    class ResourceManager:public Noncopyable {
    private:
        FileWatcher watcher;
        PointerMap<String, Resource*> resources;
        CriticalSection section;
        ResourceFactory *resourceFactory = ghnew DefaultResourceFactory();
        WorkerThread loadingThread;
        List<ReloadTask*> reloadQueue;

        Status loadInternal(Resource &resource, ResourceContext &context, const String &fileName, LoadOption options);

    public:

        ResourceManager();

        ~ResourceManager();

        void reload();

        template<class Type> Type *load(ResourceContext &context, const String &fileName, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(fileName.Length==0) {
                Logger::log(_T("file name cannot be empty\n"));
                return nullptr;
            }
            Resource *resource = get(fileName);
            Status loadResult = Status::ALREADY_LOADED;
            if(resource==nullptr) {
                resource = ghnew Type();
                loadResult = loadInternal(*resource, context, fileName, options);
                if(loadResult==Status::OK)
                    resource->release();    // resource was added to ResourceManager::resources
            }
            if(result!=nullptr)
                *result = loadResult;
            return (Type*)resource;
        }

        template<class Type> void loadAsync(ResourceContext &context, const String &fileName, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(fileName.Length==0&&onLoaded!=nullptr) {
                Logger::log(_T("file name cannot be empty\n"));
                onLoaded(nullptr, Status::INV_PARAM);
                return;
            }
            Task *task = ghnew Task(fileName, [this, &context, fileName, onLoaded, options]() {
                Resource *resource = get(fileName);
                Status result = Status::ALREADY_LOADED;
                if(resource==nullptr) {
                    resource = ghnew Type();
                    result = loadInternal(*resource, context, fileName, options);
                }
                if(onLoaded!=nullptr)
                    onLoaded((Type*)resource, result);
                return result;
            });
            loadingThread.post(task);
            task->release();
        }

        template<class Type> Type *load(ResourceContext &context, File &file, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(file.Name.Empty) {
                Logger::log(_T("file name cannot be empty\n"));
                return nullptr;
            }
            Resource *resource = get(file.Name);
            Status loadResult = Status::ALREADY_LOADED;
            if(resource==nullptr) {
                resource = ghnew Type();
                loadResult = loadInternal(*resource, context, file.Name, options);
                if(loadResult==Status::OK)
                    resource->release();    // resource was added to ResourceManager::resources
            }
            if(result!=nullptr)
                *result = loadResult;
            return (Type*)resource;
        }

        template<class Type> Type *loadAsync(ResourceContext &context, File &file, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(file.Name==nullptr&&onLoaded!=nullptr) {
                Logger::log(_T("file name cannot be empty\n"));
                onLoaded(nullptr, Status::INV_PARAM);
                return;
            }
            Task *task = ghnew Task(fileName, [this, &context, file.Name, onLoaded, options]() {
                Type *resource = get<Type>(file.Name);
                Status result = Status::ALREADY_LOADED;
                if(resource==nullptr) {
                    resource = ghnew Type();
                    result = loadInternal(*resource, context, file.Name, options);
                }
                if(onLoaded!=nullptr)
                    onLoaded(resource, result);
                return result;
            });
            loadingThread.post(task);
            task->release();
        }

        template<class Type = Resource> Type *load(ResourceContext &context, MemoryInputStream &stream, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Type *resource = (Type*)resourceFactory->makeResource(stream);
            Status loadResult;
            if(stream.readBoolean()) {
                loadResult = resource->load(*this, context, stream, options);
            } else {
                UnicodeString fileName = stream.readUnicode();
                loadResult = loadInternal(*resource, context, fileName, options);
            }
            if(result!=nullptr)
                *result = loadResult;
            return resource;
        }

        Status save(Resource &resource, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource &resource, const String &fileName, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource &resource, File &file, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource &resource, MemoryOutputStream &stream, SaveOption options = SaveOption::DEFAULT);

        Resource *get(const String &fileName);

        void add(Resource &resource);

        void remove(const String &fileName);

        void clear();
    };
}