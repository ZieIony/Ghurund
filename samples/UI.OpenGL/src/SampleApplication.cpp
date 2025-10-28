#include "SampleApplication.h"

#include <core/io/DirectoryLibrary.h>

namespace Samples {
    void SampleApplication::uninitSampleApplication() {
        delete window;
        window = nullptr;
        delete renderer;
        renderer = nullptr;

        ResourceManager.Libraries.clear();
    }

    void SampleApplication::onUninit() {
        uninitSampleApplication();
        __super::onUninit();
    }
    
    void SampleApplication::onInit() {
        __super::onInit();
        ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"test", DirectoryPath(L"./test")));
        ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"icons", DirectoryPath(L"./icons")));

        renderer = ghnew OglRenderer(parameterManager);
        renderer->init();
        window = ghnew SampleWindow(*this, *renderer);
        window->init();
        window->closed += [this](Window& window) {
            window.Visible = false;
            quit();
            return true;
        };

        window->Title = _T("Sample UI OpenGL");
        window->Size = { 800, 600 };
        window->Position = { (int)window->DecorationMetrics.Left, (int)window->DecorationMetrics.Top };
        window->Visible = true;
        window->bringToFront();
    }
}