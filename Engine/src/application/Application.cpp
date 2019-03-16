#include "Application.h"
#include <time.h>
#include "core/FunctionQueue.h"

namespace Ghurund {
    void Application::init() {
        CoInitialize(nullptr);
    
        parameterManager = ghnew Ghurund::ParameterManager();
        graphics = ghnew Ghurund::Graphics();
        graphics->init();
        audio = ghnew Ghurund::Audio();
        audio->init();
        timer = ghnew Ghurund::Timer();
        scriptEngine = ghnew Ghurund::ScriptEngine();
        scriptEngine->init(*timer);
        resourceManager = ghnew Ghurund::ResourceManager();
        resourceManager->Libraries.add(ResourceManager::ENGINE_LIB_NAME, DirectoryPath(L"."));

        resourceContext = ghnew Ghurund::ResourceContext(*graphics, *audio, *parameterManager, *scriptEngine);

        window.init(settings, *windowProc);
        window.initParameters(ParameterManager);

        renderer = ghnew Ghurund::Renderer();
        renderer->init(window, *resourceManager, *resourceContext);

        client = ghnew Ghurund::Client(windowProc->FunctionQueue);
        client->init();
    }

    void Application::uninit() {
        delete scriptEngine;

        if(client->isConnected())
            client->disconnect();
        delete client;

        delete renderer;

        timer->release();
		delete parameterManager;
        delete resourceContext;
        delete resourceManager;
        delete audio;
        delete graphics;
        window.uninit();

        CoUninitialize();
    }

    void Application::messageLoop() {
        MSG msg = {};
        while(true) {
            while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if(msg.message==WM_QUIT)
                    return;
                //TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            update();
        }
    }

    bool Application::handleMessage(SystemMessage &message) {
        if(message.code>=WM_KEYFIRST&&message.code<=WM_KEYLAST||
           message.code>=WM_MOUSEFIRST&&message.code<=WM_MOUSELAST) {
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

    void Application::run(const Settings *settings, WindowProc *proc) {
        if(settings)
            this->settings = *settings;
        if(proc == nullptr) {
            std::function<bool(SystemMessage&)> proc([this](SystemMessage &message) {return handleMessage(message); });
            windowProc = ghnew WindowProc(proc);
        } else {
            windowProc = proc;
        }

        HANDLE singleInstanceMutex = CreateMutex(nullptr, true, window.Title);
        bool alreadyRunning = GetLastError()==ERROR_ALREADY_EXISTS;

        if(!multipleInstances&&alreadyRunning) {
            MessageBox(nullptr, _T("Application is already running."), window.Title, MB_OK|MB_ICONEXCLAMATION);
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

        resourceManager->reload();

        input.dispatchEvents(levelManager);

        onUpdate();

        input.clearEvents();

        renderer->render();
    }

    void Application::reset() {
        onUninit();
        onInit();
    }

}