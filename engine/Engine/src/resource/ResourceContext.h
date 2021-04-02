#pragma once

#include "core/Noncopyable.h"
#include "core/Object.h"
#include "core/allocation/AllocatorMap.h"
#include "Status.h"

struct IWICImagingFactory;

namespace Ghurund::Audio {
    class Audio;
}

namespace Ghurund::Physics {
    class Physics;
}

namespace Ghurund {
    class Graphics;
    class Graphics2D;
    class ScriptEngine;
    class CommandList;
    class ParameterManager;
    class ResourceManager;

    class ResourceContext: public Object {
    private:
        static const Ghurund::Type& GET_TYPE();

    protected:
        Graphics& graphics;
        Ghurund::Graphics2D& graphics2d;
        Audio::Audio& audio;
        CommandList* commandList = nullptr;
        IWICImagingFactory* wicFactory = nullptr;
        ParameterManager& parameterManager;
        ScriptEngine& scriptEngine;
        Physics::Physics& physics;
        ResourceManager& resourceManager;
		AllocatorMap allocators;

    public:
        ResourceContext(Ghurund::Graphics& graphics, Ghurund::Graphics2D& graphics2d, Audio::Audio& audio, Ghurund::ParameterManager& parameterManager, ScriptEngine& scriptEngine, Physics::Physics& physics, ResourceManager& resourceManager)
            : graphics(graphics), graphics2d(graphics2d), audio(audio), parameterManager(parameterManager), scriptEngine(scriptEngine), physics(physics), resourceManager(resourceManager) {}

        ~ResourceContext();

        Status init();

        Graphics& getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics& Graphics;

        Ghurund::Graphics2D& getGraphics2D() {
            return graphics2d;
        }

        __declspec(property(get = getGraphics2D)) Ghurund::Graphics2D& Graphics2D;

        Audio::Audio& getAudio() {
            return audio;
        }

        __declspec(property(get = getAudio)) Audio::Audio& Audio;

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

        Physics::Physics& getPhysics() {
            return physics;
        }

        __declspec(property(get = getPhysics)) Physics::Physics& Physics;

        inline ResourceManager& getResourceManager() {
            return resourceManager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager& ResourceManager;

		inline AllocatorMap& getAllocators() {
			return allocators;
		}

		__declspec(property(get = getAllocators)) AllocatorMap& Allocators;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}
