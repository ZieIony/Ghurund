#pragma once

#include "ui/UIContext.h"
#include "ui/gdi/StrokeStyle.h"
#include "ui/gdi/effects/ShadowEffect.h"
#include "ui/gdi/effects/TintEffect.h"

#include <gdiplus.h>

namespace Ghurund::Core {
    class Window;
}

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;

    class UIContext:public IUIContext {
    public:
        UIContext(
            Ghurund::Core::Window& window
        ):IUIContext(window) {}

        virtual StrokeStyle* makeStrokeStyle(Array<float>& dashes) override {
            GDI::StrokeStyle* strokeStyle = ghnew GDI::StrokeStyle();
            strokeStyle->init(Gdiplus::DashStyle::DashStyleDashDot);    // TODO: use custom style
            return strokeStyle;
        }

        virtual ShadowEffect* makeShadowEffect() override {
            return ghnew Ghurund::UI::GDI::ShadowEffect();
        }

        virtual TintEffect* makeTintEffect() override {
            return ghnew Ghurund::UI::GDI::TintEffect();
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::GDI::UIContext>();
}