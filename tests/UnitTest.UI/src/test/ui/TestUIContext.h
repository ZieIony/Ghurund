#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class Window;
}

namespace UnitTest {
    class TestUIContext:public Ghurund::UI::IUIContext {
    public:
        TestUIContext(
            Ghurund::Core::Window& window
        ):IUIContext(window) {}

        virtual Ghurund::UI::IStrokeStyle* makeStrokeStyle(Ghurund::Core::Array<float>& dashes) override {
            return nullptr;
        }

        virtual Ghurund::UI::ShadowEffect* makeShadowEffect() override {
            return nullptr;
        }

        virtual Ghurund::UI::TintEffect* makeTintEffect() override {
            return nullptr;
        }
    };
}
