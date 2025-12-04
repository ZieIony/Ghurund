#include "DemoApplication.h"

namespace Demo {
    void DemoApplication::uninitDemoApplication() {
        delete renderer;
        renderer = nullptr;
        delete window;
        window = nullptr;

        delete drawableFactory;
        delete theme;
    }
    
    void DemoApplication::onInit() {
        auto graphicsFeature = Features.get<DxGraphicsFeature>();
        renderer = ghnew DxRenderer(graphicsFeature->Graphics);
        renderer->init();

        drawableFactory = ghnew Ghurund::UI::DrawableFactory(ResourceManager);
        theme = ghnew LightTheme(ResourceManager, *drawableFactory);

        window = ghnew DemoWindow(*this, *renderer, *drawableFactory);
        window->init();

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
