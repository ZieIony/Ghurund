#pragma once

#include "core/Noncopyable.h"
#include "collection/TypeMap.h"
#include "FileWatcher.h"
#include "core/Logger.h"
#include "Resource.h"
#include <memory>
#include "core/Thread.h"
#include "graphics/CommandList.h"
#include "game/ParameterManager.h"

#include <wincodec.h>

namespace Ghurund {
    class ResourceManager:public Noncopyable {
    private:
        FileWatcher *watcher;
        TypeMap<String> resources;
        CriticalSection section;
        shared_ptr<CommandList> commandList;
        Graphics &graphics;
        IWICImagingFactory *wicFactory;
        ParameterManager &parameterManager;

        WorkerThread resourceLoadingThread;

        void onFileChanged(const String &fileName, DWORD action);

        template<class Type> Status loadInternal(shared_ptr<Type> &resource, const String &fileName) {
            /*resource.reset(ghnew Type());
            Status result = resource->load(fileName, 0);
            if(result!=Status::OK) {
                Logger::log(_T("failed to load file: %s\n"), fileName.getData());
                return result;
            }

            Logger::log(_T("file loaded %s\n"), fileName.getData());
            watcher->addFile(fileName);
            section.enter();
            add(resource);
            section.leave();*/

            return Status::OK;
        }

    public:

        ResourceManager(Ghurund::Graphics &graphics, Ghurund::ParameterManager &parameterManager);

        ~ResourceManager();

        template<class Type> void load(const String &fileName, std::function<void(std::shared_ptr<Type>&, Status)> callback) {
            String *copy = ghnew String(fileName);

            resourceLoadingThread.post([copy, callback, this]() {
                std::shared_ptr<Type> resource = get<Type>(*copy);
                Status result = Status::ALREADY_LOADED;
                if(resource.get()==nullptr)
                    result = loadInternal(resource, *copy);
                callback(resource, result);
                delete copy;
            });
        }

        template<class Type> void load(const String &fileName) {
            resourceLoadingThread.post([&]() {
                std::shared_ptr<Type> resource = get<Type>(fileName);
                if(resource.get()==nullptr)
                    loadInternal(resource, fileName);
            });
        }

        template<class Type> std::shared_ptr<Type> get(const String &fileName) {
            section.enter();
            std::shared_ptr<Type> resource = resources.get<std::shared_ptr<Type>>(fileName);
            section.leave();
            return resource;
        }

        template<class Type> void add(std::shared_ptr<Type> &resource) {
            resources.set(resource->FileName, resource);
        }

        template<class Type> void remove(const String &fileName) {

        }

        Graphics &getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics &Graphics;

        ParameterManager &getParameterManager() {
            return parameterManager;
        }

        __declspec(property(get = getParameterManager)) ParameterManager &ParameterManager;

        shared_ptr<CommandList> getCommandList() {
            return commandList;
        }

        IWICImagingFactory *getImageFactory() {
            return wicFactory;
        }
    };
}