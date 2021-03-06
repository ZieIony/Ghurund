﻿#include "core/math/MathUtils.h"
#include "DemoWindow.h"

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class DemoApplication:public Application {
    public:
        DemoApplication() {
            Features.add<UIFeature>(ghnew UIFeature(*this));
        }

        void onInit() {
            auto window = ghnew DemoWindow(*this);
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->activate();
        }
    };
}
