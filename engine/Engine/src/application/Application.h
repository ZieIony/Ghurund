#pragma once

#include "ApplicationWindow.h"
#include "Settings.h"
#include "WindowList.h"

#include "core/Noncopyable.h"
#include "core/Timer.h"
#include "game/LevelManager.h"

namespace Ghurund::Net {
    class Networking;
}

namespace Ghurund::Audio {
    class Audio;
}

namespace Ghurund {
    class Graphics;
    class Renderer;
    class ScriptEngine;
    class ParameterManager;
    class Timer;
    class Graphics2D;
    class Physics::Physics;
    class FunctionQueue;

    class Application:public Noncopyable {
    private:
        WindowList windows;
        Ghurund::FunctionQueue* functionQueue = nullptr;

        Net::Networking* networking;
        Settings settings;
        Graphics* graphics;
        Audio::Audio* audio;
        Physics::Physics* physics;
        Ghurund::Graphics2D* graphics2d;

        ResourceManager* resourceManager;
        ParameterManager* parameterManager;
        Timer* timer;
        ScriptEngine* scriptEngine;

        Renderer* renderer;
        LevelManager levelManager;

        Status init();
        void handleMessages();
        void uninit();

    protected:
        virtual void onInit() {};

        virtual void onUninit() {};

    public:
        virtual ~Application() {}

        void run(const Settings* val = nullptr);

        inline void quit() {
            PostQuitMessage(0);
        }

        inline const Settings& getSettings() const {
            return settings;
        }

        __declspec(property(get = getSettings)) const Settings& Settings;

        inline WindowList& getWindows() {
            return windows;
        }

        __declspec(property(get = getWindows)) WindowList& Windows;

        FunctionQueue& getFunctionQueue() {
            return *functionQueue;
        }

        __declspec(property(get = getFunctionQueue)) FunctionQueue& FunctionQueue;

        inline Net::Networking& getNetworking() {
            return *networking;
        }

        __declspec(property(get = getNetworking)) Net::Networking& Networking;

        inline Graphics& getGraphics() {
            return *graphics;
        }

        __declspec(property(get = getGraphics)) Graphics& Graphics;

        Audio::Audio& getAudio() {
            return *audio;
        }

        __declspec(property(get = getAudio)) Audio::Audio& Audio;

        Physics::Physics& getPhysics() {
            return *physics;
        }

        __declspec(property(get = getPhysics)) Physics::Physics& Physics;

        inline ResourceManager& getResourceManager() {
            return *resourceManager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager& ResourceManager;

        inline ParameterManager& getParameterManager() {
            return *parameterManager;
        }

        __declspec(property(get = getParameterManager)) ParameterManager& ParameterManager;

        inline Timer& getTimer() {
            return *timer;
        }

        __declspec(property(get = getTimer)) Timer& Timer;

        inline LevelManager& getLevelManager() {
            return levelManager;
        }

        __declspec(property(get = getLevelManager)) LevelManager& LevelManager;

        inline Renderer& getRenderer() {
            return *renderer;
        }

        __declspec(property(get = getRenderer)) Renderer& Renderer;

        inline ScriptEngine& getScriptEngine() {
            return *scriptEngine;
        }

        __declspec(property(get = getScriptEngine)) ScriptEngine& ScriptEngine;

        inline Ghurund::Graphics2D& getGraphics2D() {
            return *graphics2d;
        }

        __declspec(property(get = getGraphics2D)) Ghurund::Graphics2D& Graphics2D;
    };
}