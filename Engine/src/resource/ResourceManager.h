#pragma once

#include "core/Noncopyable.h"
#include "collection/TypeMap.h"
#include "FileWatcher.h"
#include "core/Logger.h"
#include "Resource.h"
#include "core/Thread.h"
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
        CommandList commandList;
        Graphics &graphics;
        Audio &audio;
        IWICImagingFactory *wicFactory;
        ParameterManager &parameterManager;
        ResourceFactory *resourceFactory = ghnew DefaultResourceFactory();

        WorkerThread resourceLoadingThread;

        void onFileChanged(const String &fileName, DWORD action);

        template<class Type> Status loadInternal(Type &resource, const String &fileName, LoadOption options) {
            Status result = resource.load(*this, fileName, nullptr, options);
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

        ResourceManager(Ghurund::Graphics &graphics, Ghurund::Audio &audio, Ghurund::ParameterManager &parameterManager);

        ~ResourceManager();

        template<class Type> void load(const String &fileName, std::function<void(Type&, Status)> callback, LoadOption options = LoadOption::DEFAULT) {
            String *copy = ghnew String(fileName);

            resourceLoadingThread.post([copy, callback, this, options]() {
                Type *resource = get<Type>(*copy);
                Status result = Status::ALREADY_LOADED;
                if(resource.get()==nullptr)
                    result = loadInternal(*resource, *copy, options);
                callback(resource, result);
                delete copy;
            });
        }

        template<class Type> Type *load(const String &fileName, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(fileName.Length==0)
                return nullptr;
            Type *resource = get<Type>(fileName);
            if(resource==nullptr)
                resource = ghnew Type();
            Status loadResult = loadInternal(*resource, fileName, options);
            if(result!=nullptr)
                *result = loadResult;
            return resource;
        }

        template<class Type> Type *load(File &file, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            if(file.Name==nullptr)
                return nullptr;
            Type *resource = get<Type>(file.Name);
            if(resource==nullptr)
                resource = ghnew Type();
            Status loadResult = loadInternal(*resource, file.Name, options);
            if(result!=nullptr)
                *result = loadResult;
            return resource;
        }

        Resource *load(MemoryInputStream &stream, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Resource *resource = resourceFactory->makeResource(stream);
            Status loadResult;
            if(stream.readBoolean()) {
                loadResult = resource->load(*this, stream, options);
            } else {
                UnicodeString fileName = stream.readUnicode();
                loadResult = loadInternal(*resource, fileName, options);
            }
            if(result!=nullptr)
                *result = loadResult;
            return resource;
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

        Graphics &getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics &Graphics;

        Audio &getAudio() {
            return audio;
        }

        __declspec(property(get = getAudio)) Audio &Audio;

        ParameterManager &getParameterManager() {
            return parameterManager;
        }

        __declspec(property(get = getParameterManager)) ParameterManager &ParameterManager;

        CommandList &getCommandList() {
            return commandList;
        }

        IWICImagingFactory *getImageFactory() {
            return wicFactory;
        }
    };
}