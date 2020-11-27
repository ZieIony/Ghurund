#pragma once

#include "Settings.h"
#include "Timer.h"
#include "Window.h"
#include "WindowList.h"

#include "audio/Audio.h"
#include "core/Noncopyable.h"
#include "core/threading/FunctionQueue.h"
#include "game/parameter/ParameterManager.h"
#include "game/LevelManager.h"
#include "graphics/Graphics.h"
#include "graphics/Renderer.h"
#include "input/Input.h"
#include "net/Client.h"
#include "physics/Physics.h"
#include "resource/ResourceContext.h"
#include "resource/ResourceManager.h"
#include "script/ScriptEngine.h"
#include "ui/Graphics2D.h"

#include <thread>

namespace Ghurund {
    class Application:public Noncopyable {
    private:
        WindowList windows;
        Ghurund::FunctionQueue* functionQueue = nullptr;

        Client* client;
        Settings settings;
        Graphics* graphics;
        Audio* audio;
        Physics* physics;
        Ghurund::UI::Graphics2D* graphics2d;

        ResourceManager* resourceManager;
        ResourceContext* resourceContext, * asyncResourceContext;
        ParameterManager* parameterManager;
        Timer* timer;
        Input input;
        ScriptEngine* scriptEngine;

        Renderer* renderer;
        LevelManager levelManager;

        void init();
        void handleMessages();
        void update();
        void uninit();

    protected:
        virtual void onInit() {};

        virtual void onUninit() {};

        virtual void onUpdate() {
            levelManager.update();
        };

        /*virtual void client(const void *buffer, unsigned int size){
            if(currentFrame)
                currentFrame->client(buffer, size);
        };

        virtual void server(const Socket *socket, const void *buffer, unsigned int size){
            if(currentFrame)
                currentFrame->server(socket, buffer, size);
        };*/


    public:
        Application():windows(*this) {}

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

        inline WindowList& getWindows() {
            return windows;
        }

        __declspec(property(get = getWindows)) WindowList& Windows;

        FunctionQueue& getFunctionQueue() {
            return *functionQueue;
        }

        __declspec(property(get = getFunctionQueue)) FunctionQueue& FunctionQueue;

        inline Client& getClient() {
            return *client;
        }

        __declspec(property(get = getClient)) Client& Client;

        inline Graphics& getGraphics() {
            return *graphics;
        }

        __declspec(property(get = getGraphics)) Graphics& Graphics;

        Audio& getAudio() {
            return *audio;
        }

        __declspec(property(get = getAudio)) Audio& Audio;

        Physics& getPhysics() {
            return *physics;
        }

        __declspec(property(get = getPhysics)) Physics& Physics;

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

        inline Input& getInput() {
            return input;
        }

        __declspec(property(get = getInput)) Input& Input;

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