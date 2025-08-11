#include "DemoApplication.h"

namespace Demo {
    void DemoApplication::uninitDemoApplication() {
        delete window;
        window = nullptr;

        delete drawableFactory;
        delete theme;
    }
    
    void DemoApplication::onInit() {
        renderer.init(Features->get<Graphics>(), parameterManager);

        drawableFactory = ghnew Ghurund::UI::DrawableFactory(ResourceManager);
        theme = ghnew LightTheme(ResourceManager, *drawableFactory);

        window = ghnew DemoWindow(*this, renderer, drawableFactory);
        window->init();

        window->ClientSize = { 800, 600 };
        window->Position = { 0, 0 };
        window->Visible = true;
        window->bringToFront();
    }
    
    void DemoApplication::onUninit() {
        uninitDemoApplication();
    }
}
