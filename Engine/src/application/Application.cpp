#include "Application.h"
#include "WindowType.h"
#include "core/threading/FunctionQueue.h"

#include <time.h>

namespace Ghurund {
    void Application::init() {
        CoInitialize(nullptr);

        // engine
        graphics = ghnew Ghurund::Graphics();
        graphics->init();
        audio = ghnew Ghurund::Audio();
        audio->init();
        physics = ghnew Ghurund::Physics();
        physics->init();
        parameterManager = ghnew Ghurund::ParameterManager();

        timer = ghnew Ghurund::Timer();
        scriptEngine = ghnew Ghurund::ScriptEngine();
        scriptEngine->init(*timer);
        resourceManager = ghnew Ghurund::ResourceManager();
        resourceManager->Libraries.add(ResourceManager::ENGINE_LIB_NAME, DirectoryPath(L"."));

        resourceContext = ghnew Ghurund::ResourceContext(*graphics, *audio, *parameterManager, *scriptEngine, *physics, *resourceManager);
        resourceContext->init();
        asyncResourceContext = ghnew Ghurund::ResourceContext(*graphics, *audio, *parameterManager, *scriptEngine, *physics, *resourceManager);
        asyncResourceContext->init();
        //parameterManager->initDefaultTextures(*resourceContext);

        // app
        const WindowClass& windowType = settings.windowed ? WindowClass::WINDOWED : WindowClass::FULLSCREEN;
        window = windowType.create();
        window->initParameters(ParameterManager);
        renderer = ghnew Ghurund::Renderer();
        renderer->init(*resourceContext);
        swapChain = ghnew SwapChain();
        swapChain->init(Graphics, *window, FRAME_COUNT);

        window->OnSizeChanged.add([&](Ghurund::Window& window) {
            //swapChain->resize(args.width, args.height);
            return true;
        });

        window->Size = XMINT2(settings.width, settings.height);

        client = ghnew Ghurund::Client(window->FunctionQueue);
        client->init();
    }

    void Application::uninit() {
        delete scriptEngine;

        if (client->isConnected())
            client->disconnect();
        delete client;

        delete swapChain;
        delete renderer;

        delete timer;
        delete parameterManager;
        delete asyncResourceContext;
        delete resourceContext;
        delete resourceManager;

        delete window;
        delete physics;
        delete audio;
        delete graphics;

        CoUninitialize();
    }

 /*   bool Application::handleMessage(SystemMessage & message) {
        if (message.code >= WM_KEYFIRST && message.code <= WM_KEYLAST ||
            message.code >= WM_MOUSEFIRST && message.code <= WM_MOUSELAST) {
            input.dispatchMessage(message);
        } else if (message.code == WM_CREATE) {
            onWindowCreated();
        } else if (message.code == WM_DESTROY) {
            onWindowDestroy();
            PostQuitMessage(0);
        } else {
            return onMessage(message);
        }
        return true;
    }*/

    void Application::run(const Settings * settings) {
        if (settings)
            this->settings = *settings;

        init();
        onInit();
        window->Visible = true;
        window->activate();

        while (window->handleMessages())
            update();

        window->Visible = false;
        onUninit();
        uninit();
    }

    void Application::update() {
        timer->tick();

		float dt = timer->FrameTime;	// TODO: constant dt

        resourceManager->reload();

        input.dispatchEvents(levelManager);

        scriptEngine->update(dt);

        onUpdate();

        input.clearEvents();

		//onDraw();
    }

    void Application::reset() {
        onUninit();
        onInit();
    }

}