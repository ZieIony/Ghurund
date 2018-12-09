#pragma once

#include "audio/Audio.h"
#include "core/Noncopyable.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/CommandList.h"

#include <wincodec.h>

namespace Ghurund {
    class ResourceContext {
    protected:
        Graphics &graphics;
        Audio &audio;
        CommandList *commandList;
        IWICImagingFactory *wicFactory;
        ParameterManager &parameterManager;

    public:
        ResourceContext(Ghurund::Graphics &graphics, Ghurund::Audio &audio, Ghurund::ParameterManager &parameterManager)
            : graphics(graphics), audio(audio), parameterManager(parameterManager) {
            commandList = ghnew Ghurund::CommandList();
            commandList->init(graphics, graphics.DirectQueue);
            commandList->Name = _T("loading context's CommandList");
            HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));
        }

        ~ResourceContext() {
            wicFactory->Release();
            commandList->release();
        }

        Graphics &getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics &Graphics;

        Audio &getAudio() {
            return audio;
        }

        __declspec(property(get = getAudio)) Audio &Audio;

        CommandList &getCommandList() {
            return *commandList;
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
}
