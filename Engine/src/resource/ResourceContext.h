#pragma once

#include "audio/Audio.h"
#include "core/Noncopyable.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/CommandList.h"
#include "script/ScriptEngine.h"
#include "physics/Physics.h"

#include <wincodec.h>

namespace Ghurund {
    class ResourceContext: public Object {
    protected:
        Graphics& graphics;
        Audio& audio;
        CommandList* commandList;
        IWICImagingFactory* wicFactory;
        ParameterManager& parameterManager;
        ScriptEngine& scriptEngine;
        Physics& physics;

    public:
        ResourceContext(Ghurund::Graphics& graphics, Ghurund::Audio& audio, Ghurund::ParameterManager& parameterManager, ScriptEngine& scriptEngine, Physics& physics)
            : graphics(graphics), audio(audio), parameterManager(parameterManager), scriptEngine(scriptEngine), physics(physics) {
            commandList = ghnew Ghurund::CommandList();
            commandList->init(graphics, graphics.DirectQueue);
            commandList->Name = _T("loading context's CommandList");
            HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));
        }

        ~ResourceContext() {
            wicFactory->Release();
            commandList->release();
        }

        Graphics& getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics& Graphics;

        Audio& getAudio() {
            return audio;
        }

        __declspec(property(get = getAudio)) Audio& Audio;

        CommandList& getCommandList() {
            return *commandList;
        }

        __declspec(property(get = getCommandList)) CommandList& CommandList;

        IWICImagingFactory* getImageFactory() {
            return wicFactory;
        }

        __declspec(property(get = getImageFactory)) IWICImagingFactory* ImageFactory;

        ParameterManager& getParameterManager() {
            return parameterManager;
        }

        __declspec(property(get = getParameterManager)) ParameterManager& ParameterManager;

        ScriptEngine& getScriptEngine() {
            return scriptEngine;
        }

        __declspec(property(get = getScriptEngine)) ScriptEngine& ScriptEngine;

        Physics& getPhysics() {
            return physics;
        }

        __declspec(property(get = getPhysics)) Physics& Physics;

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}
