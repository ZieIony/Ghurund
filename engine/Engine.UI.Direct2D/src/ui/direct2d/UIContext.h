#pragma once

#include "ui/UIContext.h"
#include "ui/direct2d/StrokeStyle.h"
#include "ui/direct2d/effects/ShadowEffect.h"
#include "ui/direct2d/effects/TintEffect.h"

#include <d2d1_3.h>
#include <dwrite.h>

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class UIContext:public IUIContext {
    private:
        ID2D1Factory6& d2dFactory;
        IDWriteFactory& dwriteFactory;
        ID2D1DeviceContext5& deviceContext;

    public:
        UIContext(
            ID2D1Factory6& d2dFactory,
            IDWriteFactory& dwriteFactory,
            ID2D1DeviceContext5& deviceContext,
            Ghurund::Core::Window& window,
            Ghurund::Core::ResourceManager& manager
        ):IUIContext(window, manager), d2dFactory(d2dFactory), dwriteFactory(dwriteFactory), deviceContext(deviceContext) {}

        inline ID2D1DeviceContext5& getDeviceContext() {
            return deviceContext;
        }

        __declspec(property(get = getDeviceContext)) ID2D1DeviceContext5& DeviceContext;

        virtual StrokeStyle* makeStrokeStyle(Array<float>& dashes) override {
            Direct2D::StrokeStyle* strokeStyle = ghnew Direct2D::StrokeStyle();
            strokeStyle->init(d2dFactory, dashes);
            return strokeStyle;
        }

        virtual ShadowEffect* makeShadowEffect() override {
            return ghnew Ghurund::UI::Direct2D::ShadowEffect();
        }

        virtual TintEffect* makeTintEffect() override {
            return ghnew Ghurund::UI::Direct2D::TintEffect();
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Direct2D::UIContext>();
}