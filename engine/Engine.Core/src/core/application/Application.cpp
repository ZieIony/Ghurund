#include "ghcpch.h"
#include "Application.h"

#include "core/threading/FunctionQueue.h"
#include "core/window/SystemWindow.h"
#include "core/resource/ResourceManager.h"
#include "core/image/ImageLoader.h"
#include "core/io/DirectoryLibrary.h"

#include <time.h>

namespace Ghurund::Core {
    void Application::init() {
        CoInitialize(nullptr);
        OleInitialize(nullptr);

        resourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(ResourceManager::ENGINE_LIB_NAME, DirectoryPath(L"./resources")));

        //parameterManager->initDefaultTextures(*resourceContext);

        auto imageLoader = makeShared<ImageLoader>();
        imageLoader->init();
        resourceManager.Loaders.set<Image>(imageLoader.get());

        features.init();
    }

    void Application::uninit() {
        windows.clear();
        resourceManager.clearCache();

        features.uninit();

        OleUninitialize();
        CoUninitialize();
    }

    void Application::run(const Ghurund::Core::Settings* settings) {
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

        try {
            onInit();
        } catch (...) {
            onUninit();
            uninit();
            return;
        }
        running = true;

        timer.tick();
        uint64_t time = timer.TimeMs;
        const uint32_t DT_MS = 10;

        while (windows.Size != 0) {
            handleMessages();
            FunctionQueue.invoke();
            resourceManager.reload();

            timer.tick();
            while (time + DT_MS < timer.TimeMs) {
                time += DT_MS;
                // TODO: per window
                //scriptEngine->update(time);

                for (auto window : windows)
                    window->update(time);
            }

            for (auto window : windows) {
                if (window->Size.Width == 0 || window->Size.Height == 0)
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

    template<>
    const Type& getType<Application>() {
        static Type TYPE = Type(Ghurund::Core::NAMESPACE_NAME, "Application", sizeof(Application));
        return TYPE;
    }
}