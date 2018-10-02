#pragma once

#include "core/Noncopyable.h"
#include "graphics/CommandList.h"
#include "game/ParameterManager.h"
#include "audio/Audio.h"
#include "ResourceManager.h"

#include <wincodec.h>

namespace Ghurund {
    class BaseResourceContext {
    protected:
        ResourceManager &resourceManager;
        Graphics &graphics;
        Audio &audio;
        CommandList commandList;
        IWICImagingFactory *wicFactory;
        ParameterManager &parameterManager;

    public:
        BaseResourceContext(Ghurund::ResourceManager &resourceManager, Ghurund::Graphics &graphics, Ghurund::Audio &audio, Ghurund::ParameterManager &parameterManager)
            : resourceManager(resourceManager), graphics(graphics), audio(audio), parameterManager(parameterManager) {
            commandList.init(graphics);
            HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));
        }

        ~BaseResourceContext() {
            wicFactory->Release();
        }

        ResourceManager &getResourceManager() {
            return resourceManager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager &ResourceManager;

        Graphics &getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics &Graphics;

        Audio &getAudio() {
            return audio;
        }

        __declspec(property(get = getAudio)) Audio &Audio;

        CommandList &getCommandList() {
            return commandList;
        }

        __declspec(property(get = getCommandList)) CommandList &CommandList;

        IWICImagingFactory *getImageFactory() {
            return wicFactory;
        }

        __declspec(property(get = getImageFactory)) IWICImagingFactory *ImageFactory;

        ParameterManager &getParameterManager() {
            return parameterManager;
        }

        __declspec(property(get = getParameterManager)) ParameterManager &ParameterManager;
    };

    template<bool isAsync> class ResourceContext:public BaseResourceContext {
        void start() {}
        void finish(std::function<void()> onFinished = nullptr) {}

        template<class Type> void load(const String &fileName, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {}
        template<class Type> void load(File &file, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {}
        template<class Type> void load(MemoryInputStream &stream, Status *result = nullptr, LoadOption options = LoadOption::DEFAULT) {}
    };

    template<> class ResourceContext<false>:public BaseResourceContext {
    public:
        void start() {
            if(commandList.Closed)
                commandList.reset();
        }

        void finish(std::function<void()> onFinished = nullptr) {
            if(!commandList.Closed)
                commandList.finish();
            if(onFinished != nullptr)
                onFinished();
        }

        template<class Type> void load(const String &fileName, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Status result;
            Type *resource = resourceManager.load<Type>(fileName, &result, options);
            if(onLoaded!=nullptr)
                onLoaded(resource, result);
        }

        template<class Type> void load(File &file, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Status result;
            Type *resource = resourceManager.load<Type>(file, &result, options);
            if(onLoaded!=nullptr)
                onLoaded(resource, result);
        }
    };

    template<> class ResourceContext<true>:public BaseResourceContext {
    private:
        WorkerThread resourceLoadingThread;

    public:
        ResourceContext(Ghurund::ResourceManager &resourceManager, Ghurund::Graphics &graphics, Ghurund::Audio &audio, Ghurund::ParameterManager &parameterManager)
            : BaseResourceContext(resourceManager, graphics, audio, parameterManager) {
            resourceLoadingThread.start();
        }

        ~ResourceContext() {
            resourceLoadingThread.finish();
        }

        void start() {
            resourceLoadingThread.post("start loading", [&]() {
                if(commandList.Closed)
                    commandList.reset();
                return Status::OK;
            });
        }

        void finish(std::function<void()> onFinished = nullptr) {
            resourceLoadingThread.post("finish loading", [&]() {
                if(!commandList.Closed)
                    commandList.finish();
                if(onFinished != nullptr)
                    onFinished();
                return Status::OK;
            });
        }

        template<class Type> void load(const String &fileName, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            resourceLoadingThread.post(fileName, [&, fileName, onLoaded, options]() {
                Status result;
                Type *resource = resourceManager.load<Type>(fileName, &result, options);
                if(onLoaded!=nullptr)
                    onLoaded(resource, result);
                return result;
            });
        }

        template<class Type> void load(File &file, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            resourceLoadingThread.post(file.Name, [&, file, onLoaded, options]() {
                Status result;
                Type *resource = resourceManager.load<Type>(file, &result, options);
                if(onLoaded!=nullptr)
                    onLoaded(resource, result);
                return result;
            });
        }
    };
}