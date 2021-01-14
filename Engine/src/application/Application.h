#pragma once

#include "Settings.h"
#include "Timer.h"
#include "Window.h"

#include "core/Noncopyable.h"
#include "game/LevelManager.h"

namespace Ghurund::Net {
    class Networking;
}

namespace Ghurund {
    class Graphics;
    class Audio::Audio;
    class Renderer;
    class ScriptEngine;
    class ParameterManager;
    class Timer;
    class ResourceContext;
    class UI::Graphics2D;
    class Physics::Physics;
    class FunctionQueue;

    class Application:public Noncopyable {
    private:
        List<SystemWindow*> windows;
        Ghurund::FunctionQueue* functionQueue = nullptr;

        Net::Networking* networking;
        Settings settings;
        Graphics* graphics;
        Audio::Audio* audio;
        Physics::Physics* physics;
        Ghurund::UI::Graphics2D* graphics2d;

        ResourceManager* resourceManager;
        ResourceContext* resourceContext, * asyncResourceContext;
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

        /*virtual void client(const void *buffer, unsigned int size){
            if(currentFrame)
                currentFrame->client(buffer, size);
        };

        virtual void server(const Socket *socket, const void *buffer, unsigned int size){
            if(currentFrame)
                currentFrame->server(socket, buffer, size);
        };*/


    public:
        virtual ~Application() {}

        void run(const Settings* val = nullptr);

        inline void quit() {
            PostQuitMessage(0);
        }

        void reset();

        inline const Settings& getSettings() const {
            return settings;
        }

        __declspec(property(get = getSettings)) const Settings& Settings;

        inline List<SystemWindow*>& getWindows() {
            return windows;
        }

        __declspec(property(get = getWindows)) List<SystemWindow*>& Windows;

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

        inline ResourceContext& getResourceContext() {
            return *resourceContext;
        }

        __declspec(property(get = getResourceContext)) ResourceContext& ResourceContext;

        inline Ghurund::ResourceContext& getAsyncResourceContext() {
            return *asyncResourceContext;
        }

        __declspec(property(get = getAsyncResourceContext)) Ghurund::ResourceContext& AsyncResourceContext;

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

        inline Ghurund::UI::Graphics2D& getGraphics2D() {
            return *graphics2d;
        }

        __declspec(property(get = getGraphics2D)) Ghurund::UI::Graphics2D& Graphics2D;
    };
}