#include "ghpch.h"
#include "Application.h"

#include "audio/Audio.h"
#include "core/threading/FunctionQueue.h"
#include "core/window/SystemWindow.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/Graphics.h"
#include "graphics/Graphics2D.h"
#include "graphics/Renderer.h"
#include "physics/Physics.h"
#include "core/resource/ResourceManager.h"
#include "script/ScriptEngine.h"

#include "net/Networking.h"

#include <time.h>

namespace Ghurund {
    Status Application::init() {
        CoInitialize(nullptr);
        OleInitialize(nullptr);
        networking = ghnew Net::Networking();
        Status result = networking->init();
        if (result != Status::OK) {
            uninit();
            return result;
        }

        // engine
        graphics = ghnew Ghurund::Graphics();
        result = graphics->init();
        if (result != Status::OK)
            return result;

        graphics2d = ghnew Ghurund::Graphics2D();
        result = graphics2d->init(*graphics);
        if (result != Status::OK)
            return result;

        audio = ghnew Audio::Audio();
        result = audio->init();
        if (result != Status::OK)
            return result;

        physics = ghnew Physics::Physics();
        result = physics->init();
        if (result != Status::OK)
            return result;

        parameterManager = ghnew Ghurund::ParameterManager();

        timer = ghnew Ghurund::Timer();

        scriptEngine = ghnew Ghurund::ScriptEngine();
        result = scriptEngine->init(*timer);
        if (result != Status::OK)
            return result;

        resourceManager = ghnew Ghurund::ResourceManager();
        resourceManager->Libraries.add(ResourceManager::ENGINE_LIB_NAME, DirectoryPath(L"."));

        //parameterManager->initDefaultTextures(*resourceContext);

        functionQueue = ghnew Ghurund::FunctionQueue();

        renderer = ghnew Ghurund::Renderer();
        result = renderer->init(*graphics, *parameterManager);
        if (result != Status::OK)
            return result;

        return Status::OK;
    }

    void Application::uninit() {
        windows.clear();

        delete scriptEngine;

        delete renderer;

        delete timer;
        delete parameterManager;
        delete resourceManager;

        delete functionQueue;
        delete physics;
        delete audio;
        delete graphics2d;
        delete graphics;

        delete networking;
        OleUninitialize();
        CoUninitialize();
    }

    void Application::run(const Ghurund::Settings* settings) {
        if (settings)
            this->settings = *settings;

        if (init() != Status::OK) {
            uninit();
            return;
        }

        onInit();

        timer->tick();
        uint64_t time = timer->TimeMs;
        const uint32_t DT_MS = 10;

        while (windows.Size != 0) {
            handleMessages();
            FunctionQueue.invoke();
            resourceManager->reload();

            timer->tick();
            while (time + DT_MS < timer->TimeMs) {
                time += DT_MS;
                scriptEngine->update(time);

                for (auto window : windows)
                    window->update(time);
            }

            for (auto window : windows) {
                if (window->Size.width == 0 && window->Size.height == 0)
                    continue;
                if (window->SwapChain) {
                    Frame& frame = window->SwapChain->CurrentFrame;
                    CommandList& commandList = renderer->startFrame(frame);
                    //levelManager.draw(commandList);
                    frame.flush();

                    if (window->paint() != Status::OK)
                        break;

                    if (renderer->finishFrame(frame) != Status::OK)
                        break;
                    if (window->SwapChain->present() != Status::OK)
                        break;
                } else {
                    if (window->paint() != Status::OK)
                        break;
                }
            }
        }

        onUninit();
        uninit();
    }

    void Application::handleMessages() {
        MSG msg = {};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                for (auto w : windows)
                    delete w;
                windows.clear();
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}