#include "SampleApplication.h"

#include "SampleWindow.h"

namespace Sample {
    void SampleApplication::uninitDemoApplication() {
        delete renderer;
        renderer = nullptr;
        delete window;
        window = nullptr;
    }

    void SampleApplication::onInit() {
        __super::onInit();

        renderer = ghnew OglRenderer(parameterManager);
        renderer->init();

        window = ghnew SampleWindow(*this, *renderer);
        window->ClientSize = { 800, 600 };
        window->Position = { 0, 0 };
        window->Visible = true;
        window->bringToFront();
    }
    
    void SampleApplication::onUninit() {
        uninitDemoApplication();
        __super::onUninit();
    }
}
