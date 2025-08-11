#include "DemoApplication.h"

#include "DemoWindow.h"

namespace Demo {
    void DemoApplication::onInit() {
        renderer.init(Features->get<Graphics>(), parameterManager);

        window = ghnew DemoWindow(*this, renderer);
		window->ClientSize = { 800, 600 };
        window->Position = { 0, 0 };
        window->Visible = true;
        window->bringToFront();
    }
    
    void DemoApplication::onUninit() {
        delete window;
        window = nullptr;
    }
}