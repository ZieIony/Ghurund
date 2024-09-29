#pragma once

#include "ui/UIContext.h"
#include "ui/opengl/StrokeStyle.h"
#include "ui/opengl/effects/ShadowEffect.h"
#include "ui/opengl/effects/TintEffect.h"

#include <gdiplus.h>

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI::OpenGL {
    using namespace Ghurund::Core;

    class UIContext:public IUIContext {
    public:
        UIContext(
            Ghurund::Core::Window& window
        ):IUIContext(window) {}

        virtual StrokeStyle* makeStrokeStyle(Array<float>& dashes) override {
            OpenGL::StrokeStyle* strokeStyle = ghnew OpenGL::StrokeStyle();
            strokeStyle->init(Gdiplus::DashStyle::DashStyleDashDot);    // TODO: use custom style
            return strokeStyle;
        }

        virtual ShadowEffect* makeShadowEffect() override {
            return ghnew Ghurund::UI::OpenGL::ShadowEffect();
        }

        virtual TintEffect* makeTintEffect() override {
            return ghnew Ghurund::UI::OpenGL::TintEffect();
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::OpenGL::UIContext>();
}