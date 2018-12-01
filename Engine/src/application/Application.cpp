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
        resourceManager = ghnew Ghurund::ResourceManager();
        resourceContext = ghnew Ghurund::ResourceContext(*graphics, *audio, *parameterManager);

        window.init(settings, *windowProc);
        window.initParameters(ParameterManager);
        renderer.init(*graphics, window);

        client = ghnew Ghurund::Client(windowProc->FunctionQueue);
        client->init();
    }

    void Application::uninit() {
        if(client->isConnected())
            client->disconnect();
        delete client;

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

        renderer.uninit();
        window.Visible = false;
        onUninit();
        uninit();

        delete windowProc;


    cleanUp:
        CloseHandle(singleInstanceMutex);
    }

    void Application::update() {
        ticks_t prevTicks = timer.CurrentTicks;
        timer.tick();
        ticks_t currentTicks = timer.CurrentTicks;

        resourceManager->reload();

        input.dispatchEvents(levelManager);

        onUpdate();
        levelManager.update();

        input.clearEvents();

        renderer.startFrame();
        levelManager.draw(renderer, ParameterManager);
        renderer.finishFrame();
    }

    void Application::reset() {
        onUninit();
        onInit();
    }

}