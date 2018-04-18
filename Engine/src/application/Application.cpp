#include "Application.h"
#include <time.h>
#include "core/FunctionQueue.h"
#include "ApplicationWindowProc.h"

namespace Ghurund {
    void Application::initInternal() {
        parameterManager = ghnew Ghurund::ParameterManager();
        graphics = ghnew Ghurund::Graphics();
        graphics->init();
        resourceManager = ghnew Ghurund::ResourceManager(*graphics, *parameterManager);

        window.init(settings, *windowProc);
        window.initParameters(ParameterManager);
        renderer.init(*graphics, window);

        client = ghnew Ghurund::Client(windowProc->FunctionQueue);
        client->init();
    }

    void Application::uninitInternal() {
        if(client->isConnected())
            client->disconnect();
        delete client;

        delete parameterManager;
        delete resourceManager;
        delete graphics;
        window.uninit();
    }

    void Application::messageLoop() {
        MSG msg = {};
        while(true) {
            while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if(msg.message==WM_QUIT)
                    return;
                handleMessage(msg);
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            update();
        }
    }

    void Application::handleMessage(MSG &msg) {
        if(msg.message==WM_KEYDOWN) {
            input.dispatchKeyEvent(KeyEvent(KeyAction::DOWN, msg.wParam, msg.time));
        } else if(msg.message==WM_KEYUP) {
            input.dispatchKeyEvent(KeyEvent(KeyAction::UP, msg.wParam, msg.time));
        } else if(msg.message==WM_LBUTTONDOWN) {
            input.dispatchMouseButtonEvent(MouseButtonEvent(MouseAction::DOWN, MouseButton::LEFT, msg.time));
        } else if(msg.message==WM_LBUTTONUP) {
            //windowProc->onMouseButton(MouseButton::LEFT, MouseAction::UP);
        } else if(msg.message==WM_MBUTTONDOWN) {
            //windowProc->onMouseButton(MouseButton::MIDDLE, MouseAction::DOWN);
        } else if(msg.message==WM_MBUTTONUP) {
            //windowProc->onMouseButton(MouseButton::MIDDLE, MouseAction::UP);
        } else if(msg.message==WM_RBUTTONDOWN) {
            //windowProc->onMouseButton(MouseButton::RIGHT, MouseAction::DOWN);
        } else if(msg.message==WM_RBUTTONUP) {
            //windowProc->onMouseButton(MouseButton::RIGHT, MouseAction::UP);
        } else if(msg.message==WM_MOUSEMOVE) {
            //windowProc->onMouseMove(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam));
        } else if(msg.message==WM_MOUSEWHEEL) {
            //windowProc->onMouseWheel(MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(msg.wParam));
        } else if(msg.message==WM_MOUSEHWHEEL) {
            //windowProc->onMouseWheel(MouseWheel::HORIZONTAL, msg.wParam);
        }
    }

    void Application::run(const Settings *settings, WindowProc *proc) {
        if(settings)
            this->settings = *settings;
        if(proc == nullptr) {
            windowProc = ghnew ApplicationWindowProc(*this);
        } else {
            windowProc = proc;
        }

        HANDLE singleInstanceMutex = CreateMutex(nullptr, true, window.Title);
        bool alreadyRunning = GetLastError()==ERROR_ALREADY_EXISTS;

        if(!multipleInstances&&alreadyRunning) {
            MessageBox(nullptr, _T("Application is already running."), window.Title, MB_OK|MB_ICONEXCLAMATION);
            goto cleanUp;
        }

        initInternal();
        init();
        window.Visible = true;

        messageLoop();

        window.Visible = false;
        uninit();
        uninitInternal();


    cleanUp:
        CloseHandle(singleInstanceMutex);
    }

    bool Application::update() {
        ticks_t prevTicks = timer.CurrentTicks;
        timer.tick();
        ticks_t currentTicks = timer.CurrentTicks;

        input.dispatchEvents(game);

        //while()
            //game.Update(deltaTime);

        //input.dispatchEvents(layout);

        input.clearEvents();

        levelManager.draw(renderer, *parameterManager);

        return true;
    }

    void Application::reset() {
        uninit();
        init();
    }

}