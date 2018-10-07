#pragma once

#include "core/Noncopyable.h"
#include "collection/TypeMap.h"
#include "FileWatcher.h"
#include "core/Logger.h"
#include "Resource.h"
#include "core/WorkerThread.h"
#include "graphics/CommandList.h"
#include "game/ParameterManager.h"
#include "ResourceFactory.h"
#include "audio/Audio.h"

#include <wincodec.h>

namespace Ghurund {
    class ResourceManager:public Noncopyable {
    private:
        FileWatcher *watcher;
        TypeMap<String> resources;
        CriticalSection section;
        ResourceFactory *resourceFactory = ghnew DefaultResourceFactory();
        WorkerThread loadingThread;

        void onFileChanged(const String &fileName, DWORD action);

        template<class Type> Status loadInternal(Type &resource, ResourceContext &context, const String &fileName, LoadOption options) {
            Status result = resource.load(*this, context, fileName, nullptr, options);
            if(result!=Status::OK) {
                Logger::log(_T("failed to load file: %s\n"), fileName.getData());
                return result;
            }

            //watcher->addFile(fileName);

            section.enter();
            //add(&resource);
            section.leave();

            return Status::OK;
        }

    public:

        ResourceManager();

        ~ResourceManager();

        template<class Type> Type *load(ResourceContext &context, const String &fileName, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(fileName.Length==0) {
                Logger::log(_T("file name cannot be empty\n"));
                return nullptr;
            }
            Type *resource = get<Type>(fileName);
            if(resource==nullptr)
                resource = ghnew Type();
            Status loadResult = loadInternal(*resource, context, fileName, options);
            if(result!=nullptr)
                *result = loadResult;
            return resource;
        }

        template<class Type> void loadAsync(ResourceContext &context, const String &fileName, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(fileName.Length==0&&onLoaded!=nullptr) {
                Logger::log(_T("file name cannot be empty\n"));
                onLoaded(nullptr, Status::INV_PARAM);
                return;
            }
            loadingThread.post(fileName, [this, &context, fileName, onLoaded, options]() {
                Type *resource = get<Type>(fileName);
                if(resource==nullptr)
                    resource = ghnew Type();
                Status result = loadInternal(*resource, context, fileName, options);
                if(onLoaded!=nullptr)
                    onLoaded(resource, result);
                return result;
            });
        }

        template<class Type> Type *load(ResourceContext &context, File &file, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(file.Name==nullptr) {
                Logger::log(_T("file name cannot be empty\n"));
                return nullptr;
            }
            Type *resource = get<Type>(file.Name);
            if(resource==nullptr)
                resource = ghnew Type();
            Status loadResult = loadInternal(*resource, context, file.Name, options);
            if(result!=nullptr)
                *result = loadResult;
            return resource;
        }

        template<class Type> Type *loadAsync(ResourceContext &context, File &file, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(file.Name==nullptr&&onLoaded!=nullptr) {
                Logger::log(_T("file name cannot be empty\n"));
                onLoaded(nullptr, Status::INV_PARAM);
                return;
            }
            loadingThread.post(fileName, [this, &context, fileName, onLoaded, options]() {
                Type *resource = get<Type>(file.Name);
                if(resource==nullptr)
                    resource = ghnew Type();
                Status result = loadInternal(*resource, context, file.Name, options);
                if(onLoaded!=nullptr)
                    onLoaded(resource, result);
                return result;
            });
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

        Status save(Resource &resource, SaveOption options = SaveOption::DEFAULT) {
            return resource.save(*this, options);
        }

        Status save(Resource &resource, const String &fileName, SaveOption options = SaveOption::DEFAULT) {
            if(resource.FileName.Empty) {
                Logger::log(_T("The file name is empty\n"));
                return Status::INV_PARAM;
            } else {
                return resource.save(*this, fileName, options);
            }
        }

        Status save(Resource &resource, File &file, SaveOption options = SaveOption::DEFAULT) {
            if(file.Name == nullptr) {
                Logger::log(_T("The file's name is null\n"));
                return Status::INV_PARAM;
            } else {
                return resource.save(*this, file, options);
            }
        }

        Status save(Resource &resource, MemoryOutputStream &stream, SaveOption options = SaveOption::DEFAULT) {
            resourceFactory->describeResource(resource, stream);
            if(resource.FileName.Empty) {
                stream.writeBoolean(true);  // full binary
                return resource.save(*this, stream, options);
            } else {
                stream.writeBoolean(false); // file reference
                stream.writeUnicode(resource.FileName);
                return resource.save(*this, resource.FileName, options);
            }
        }

        template<class Type> Type *get(const String &fileName) {
            section.enter();
            Type *resource = resources.get<Type*>(fileName);
            section.leave();
            return resource;
        }

        template<class Type> void add(Type &resource) {
            resources.set(resource->FileName, &resource);
        }

        template<class Type> void remove(const String &fileName) {
            resources.remove<Type>(fileName);
        }

        void clear() {}
    };
}