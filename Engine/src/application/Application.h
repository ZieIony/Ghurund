#pragma once

#include <thread>
#include "Ghurund.h"
#include "Settings.h"
#include "Window.h"
#include "WindowProc.h"
#include "net/Client.h"
#include "core/Noncopyable.h"
#include "core/Timer.h"
#include "core/FunctionQueue.h"
#include "graphics/Graphics.h"
#include "graphics/Renderer.h"
#include "resource/ResourceManager.h"
#include "input/Input.h"
#include "game/ParameterManager.h"
#include "game/LevelManager.h"
#include "audio/Audio.h"
#include "resource/ResourceContext.h"

namespace Ghurund {

    class Application:public Noncopyable {
    private:
        Window window;
        WindowProc *windowProc;

        Client *client;
        Settings settings;
        Graphics *graphics;
        Audio *audio;
        ResourceManager *resourceManager;
        ResourceContext *resourceContext;
        ParameterManager *parameterManager;
        Timer timer;
        Input input;

        Renderer renderer;
        LevelManager levelManager;

        bool multipleInstances;
        HANDLE singleInstanceMutex;

        void initInternal();
        void updateInternal();
        void uninitInternal();

        void messageLoop();

        void handleMessage(MSG & msg);

    protected:
        virtual void init() {};

        virtual void uninit() {};

        virtual void update() {};

        /*virtual void client(const void *buffer, unsigned int size){
            if(currentFrame)
                currentFrame->client(buffer, size);
        };

        virtual void server(const Socket *socket, const void *buffer, unsigned int size){
            if(currentFrame)
                currentFrame->server(socket, buffer, size);
        };*/

        virtual void onCreated() {}

        virtual void onDestroy() {}

        virtual bool onMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
            return false;
        }

        virtual void onSizeChanged() {
            Window.updateSize();
            Renderer.resize(Window.Width, Window.Height);
            Window.fillParameters();
        }

        /*
        if(event.getAction()==KeyAction::DOWN&&event.getKey()==VK_ESCAPE) {
            PostQuitMessage(0);
        }*/


    public:

        Application() = default;

        virtual ~Application() {
        }

        void run(const Settings *val = nullptr, WindowProc *proc = nullptr);

        inline void quit() {
            PostQuitMessage(0);
        }

        inline void setAllowMultipleInstances(bool multipleInstances) {
            this->multipleInstances = multipleInstances;
        }

        void reset();

        inline Window &getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Window &Window;

        inline Client &getClient() {
            return *client;
        }

        __declspec(property(get = getClient)) Client &Client;

        inline Graphics &getGraphics() {
            return *graphics;
        }

        __declspec(property(get = getGraphics)) Graphics &Graphics;

        Audio &getAudio() {
            return *audio;
        }

        __declspec(property(get = getAudio)) Audio &Audio;

        inline ResourceManager &getResourceManager() {
            return *resourceManager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager &ResourceManager;

        inline ResourceContext &getResourceContext() {
            return *resourceContext;
        }

        __declspec(property(get = getResourceContext)) ResourceContext &ResourceContext;

        inline ParameterManager &getParameterManager() {
            return *parameterManager;
        }

        __declspec(property(get = getParameterManager)) ParameterManager &ParameterManager;

        inline Timer &getTimer() {
            return timer;
        }

        __declspec(property(get = getTimer)) Timer &Timer;

        inline Input &getInput() {
            return input;
        }

        __declspec(property(get = getInput)) Input &Input;

        inline LevelManager &getLevelManager() {
            return levelManager;
        }

        __declspec(property(get = getLevelManager)) LevelManager &LevelManager;

        inline Renderer &getRenderer() {
            return renderer;
        }

        __declspec(property(get = getRenderer)) Renderer &Renderer;
    };
}