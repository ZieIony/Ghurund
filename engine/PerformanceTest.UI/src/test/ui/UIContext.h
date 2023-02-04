#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace UnitTest {
    class UIContext:public Ghurund::UI::IUIContext {
    public:
        UIContext(
            Ghurund::Core::Window& window,
            Ghurund::Core::ResourceManager& manager
        ):IUIContext(window, manager) {}

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
