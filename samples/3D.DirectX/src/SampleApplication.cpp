#include "SampleApplication.h"

#include "SampleWindow.h"

namespace Sample {
    void SampleApplication::uninitSampleApplication() {
        delete window;
        window = nullptr;
    }

    void SampleApplication::onInit() {
        __super::onInit();

        window = ghnew SampleWindow(*this);
		window->ClientSize = { 800, 600 };
        window->Position = { 0, 0 };
        window->Visible = true;
        window->bringToFront();
    }
    
    void SampleApplication::onUninit() {
        uninitSampleApplication();
        __super::onUninit();
    }
}
