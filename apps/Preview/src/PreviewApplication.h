﻿#include "PreviewWindow.h"
#include "ui/UIFeature.h"

namespace Preview {
    class PreviewApplication:public Ghurund::Application {
    public:
        PreviewApplication() {
            Features.add<UIFeature>(ghnew UIFeature(*this));
        }

        void onInit() {
            auto window = ghnew PreviewWindow(*this);
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->activate();
        }
    };
}
