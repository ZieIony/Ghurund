#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;

    class UIContext:public IUIContext {
    public:
        UIContext(
            Ghurund::Core::Window& window
        ):IUIContext(window) {}

        virtual IStrokeStyle* makeStrokeStyle(Array<float>& dashes) override {
            return nullptr;
        }

        virtual ShadowEffect* makeShadowEffect() override {
            return nullptr;
        }

        virtual TintEffect* makeTintEffect() override {
            return nullptr;
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::UIContext>();
}