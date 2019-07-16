#pragma once

#include "Settings.h"
#include "Window.h"
#include "WindowProc.h"

#include "audio/Audio.h"
#include "core/Noncopyable.h"
#include "core/Timer.h"
#include "core/FunctionQueue.h"
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

#include <thread>

namespace Ghurund {

    class Application:public Noncopyable {
    private:
        static const unsigned int FRAME_COUNT = 3;

        Window window;
        WindowProc* windowProc;

        Client* client;
        Settings settings;
        Graphics* graphics;
        Audio* audio;
        Physics* physics;

        ResourceManager* resourceManager;
        ResourceContext* resourceContext, * asyncResourceContext;
        ParameterManager* parameterManager;
        Timer* timer;
        Input input;
        ScriptEngine* scriptEngine;

        Renderer* renderer;
        SwapChain* swapChain = nullptr;
        LevelManager levelManager;

        bool multipleInstances;
        HANDLE singleInstanceMutex;

        void init();
        void update();
        void uninit();

        void messageLoop();

        bool handleMessage(SystemMessage& message);

    protected:
        virtual void onInit() {};

        virtual void onUninit() {};

        virtual void onUpdate() {
            levelManager.update();
        };

        virtual void onDraw() {
			Frame& frame = swapChain->getFrame();
			CommandList& commandList = renderer->startFrame(frame);
			levelManager.draw(commandList);
			renderer->finishFrame(frame);
			swapChain->present();
        };

        /*virtual void client(const void *buffer, unsigned int size){
            if(currentFrame)
                currentFrame->client(buffer, size);
        };

        virtual void server(const Socket *socket, const void *buffer, unsigned int size){
            if(currentFrame)
                currentFrame->server(socket, buffer, size);
        };*/

        virtual void onWindowCreated() {}

        virtual void onWindowDestroy() {}

        virtual bool onMessage(SystemMessage& message) {
            return false;
        }

        virtual void onSizeChanged() {
            Window.updateSize();
            swapChain->resize(Window.Width, Window.Height);
            Window.updateParameters();
        }


    public:

        Application() = default;

        virtual ~Application() {}

        void run(const Settings* val = nullptr, WindowProc* proc = nullptr);

        inline void quit() {
            PostQuitMessage(0);
        }

        inline void setAllowMultipleInstances(bool multipleInstances) {
            this->multipleInstances = multipleInstances;
        }

        void reset();

        inline Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Window& Window;

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
    };
}