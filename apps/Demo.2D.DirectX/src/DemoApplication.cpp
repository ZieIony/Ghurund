#include "DemoApplication.h"

#include "DemoWindow.h"

namespace Demo {
    void DemoApplication::uninitDemoApplication() {
        delete renderer;
        renderer = nullptr;
        delete window;
        window = nullptr;
    }

    void DemoApplication::onInit() {
        __super::onInit();

        renderer = ghnew DxRenderer(Features.get<DxGraphicsFeature>()->Graphics);
        renderer->init();

        window = ghnew DemoWindow(*this, *renderer);
		window->ClientSize = { 800, 600 };
        window->Position = { 0, 0 };
        window->Visible = true;
        window->bringToFront();
    }
    
    void DemoApplication::onUninit() {
        uninitDemoApplication();
        __super::onUninit();
    }
}
