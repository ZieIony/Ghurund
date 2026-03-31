#include "ghcpch.h"
#include "Application.h"

#include "core/threading/FunctionQueue.h"
#include "core/window/SystemWindow.h"
#include "core/resource/ResourceManager.h"
#include "core/image/ImageLoader.h"
#include "core/io/DirectoryLibrary.h"

namespace Ghurund::Core {
    void Application::uninitApplication() {
        windows.clear();

        resourceManager.Libraries.clear();
        resourceManager.Loaders.clear();
        resourceManager.clearCache();

        features.uninit();
    }

    void Application::onInit() {
        resourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(ResourceManager::ENGINE_LIB_NAME, DirectoryPath(L"./resources")));

        //parameterManager->initDefaultTextures(*resourceContext);

        auto imageLoader = makeIntrusive<ImageLoader>();
        resourceManager.Loaders.set<Image>(*imageLoader.get());

        features.init();
    }

    void Application::onUninit() {
        uninitApplication();
    }

    void Application::run(const Ghurund::Core::Settings* settings) {
        if (running)
            return;

        if (settings)
            this->settings = *settings;

        init();
        running = true;

        timer.tick();

        while (windows.Size != 0) {
            if (handleMessages())
                break;

            timer.tick();
            coroutineScheduler.update();
            for (auto window : windows)
                window->update();

            for (auto window : windows) {
                if (window->Size.Width == 0 || window->Size.Height == 0 || !window->Visible)
                    continue;
                window->paint();
            }
        }

        running = false;
        uninit();
    }

    bool Application::handleMessages() {
        MSG msg = {};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                return true;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return false;
    }

    template<>
    const Type& getType<Application>() {
        static Type TYPE = TypeBuilder<Application>();
        return TYPE;
    }
}