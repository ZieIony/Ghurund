#include "ghpch.h"
#include "Application.h"

#include "audio/Audio.h"
#include "core/threading/FunctionQueue.h"
#include "core/window/SystemWindow.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/Graphics.h"
#include "graphics/Renderer.h"
#include "physics/Physics.h"
#include "core/resource/ResourceManager.h"
#include "script/ScriptEngine.h"

#include "net/Networking.h"

#include <time.h>

namespace Ghurund {
    void Application::init() {
        CoInitialize(nullptr);
        OleInitialize(nullptr);

        // engine
        graphics = ghnew Ghurund::Graphics();
        graphics->init();
        graphics->initDevice(*graphics->Adapters[0]);

        parameterManager = ghnew Ghurund::ParameterManager();

        timer = ghnew Ghurund::Timer();

        resourceManager = ghnew Ghurund::ResourceManager();
        resourceManager->Libraries.add(ResourceManager::ENGINE_LIB_NAME, DirectoryPath(L"./resources"));

        //parameterManager->initDefaultTextures(*resourceContext);

        functionQueue = ghnew Ghurund::FunctionQueue();

        renderer = ghnew Ghurund::Renderer();
        renderer->init(*graphics, *parameterManager);

        for (Feature* f : features)
            f->init();
    }

    void Application::uninit() {
        windows.clear();
        resourceManager->clear();

        for (Feature* f : features)
            f->uninit();

        delete renderer;

        delete timer;
        delete parameterManager;
        delete resourceManager;

        delete functionQueue;
        delete graphics;

        OleUninitialize();
        CoUninitialize();
    }

    void Application::run(const Ghurund::Settings* settings) {
        if (running)
            return;

        if (settings)
            this->settings = *settings;

        try {
            init();
        } catch (...) {
            uninit();
            return;
        }

        if (onInit() != Status::OK) {
            onUninit();
            uninit();
            return;
        }
        running = true;

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
                // TODO: per window
                //scriptEngine->update(time);

                for (auto window : windows)
                    window->update(time);
            }

            for (auto window : windows) {
                if (window->Size.width == 0 || window->Size.height == 0)
                    continue;
                if (window->paint() != Status::OK)
                    break;
            }
        }

        running = false;
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

namespace Ghurund::Core {
    template<>
    const Type& getType<Application>() {
        static Type TYPE = Type(Ghurund::NAMESPACE_NAME, "Application", sizeof(Application));
        return TYPE;
    }
}