#include "Application.h"
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
        parameterManager->initDefaultTextures(*resourceContext);

        // app
        window.init(settings, *windowProc);
        window.initParameters(ParameterManager);
        renderer = ghnew Ghurund::Renderer();
        renderer->init(*resourceContext);
        swapChain = ghnew SwapChain();
        swapChain->init(Graphics, window, FRAME_COUNT);

        client = ghnew Ghurund::Client(windowProc->FunctionQueue);
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

        delete physics;
        delete audio;
        delete graphics;
        window.uninit();

        CoUninitialize();
    }

    void Application::messageLoop() {
        MSG msg = {};
        while (true) {
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT)
                    return;
                //TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            update();
        }
    }

    bool Application::handleMessage(SystemMessage & message) {
        if (message.code >= WM_KEYFIRST && message.code <= WM_KEYLAST ||
            message.code >= WM_MOUSEFIRST && message.code <= WM_MOUSELAST) {
            input.dispatchMessage(message);
        } else if (message.code == WM_SIZE) {
            onSizeChanged();
        } else if (message.code == WM_CREATE) {
            onWindowCreated();
        } else if (message.code == WM_DESTROY) {
            onWindowDestroy();
            PostQuitMessage(0);
        } else {
            return onMessage(message);
        }
        return true;
    }

    void Application::run(const Settings * settings, WindowProc * proc) {
        if (settings)
            this->settings = *settings;
        if (proc == nullptr) {
            std::function<bool(SystemMessage&)> proc([this](SystemMessage & message) {return handleMessage(message); });
            windowProc = ghnew WindowProc(proc);
        } else {
            windowProc = proc;
        }

        HANDLE singleInstanceMutex = CreateMutex(nullptr, true, window.Title);
        bool alreadyRunning = GetLastError() == ERROR_ALREADY_EXISTS;

        if (!multipleInstances && alreadyRunning) {
            MessageBox(nullptr, _T("Application is already running."), window.Title, MB_OK | MB_ICONEXCLAMATION);
            goto cleanUp;
        }

        init();
        onInit();
        window.Visible = true;

        messageLoop();

        window.Visible = false;
        onUninit();
        uninit();

        delete windowProc;


    cleanUp:
        CloseHandle(singleInstanceMutex);
    }

    void Application::update() {
        timer->tick();

		float dt = timer->FrameTime;	// TODO: constant dt

        resourceManager->reload();

        input.dispatchEvents(levelManager);

        scriptEngine->update(dt);

        onUpdate();

        input.clearEvents();

		onDraw();
    }

    void Application::reset() {
        onUninit();
        onInit();
    }

}