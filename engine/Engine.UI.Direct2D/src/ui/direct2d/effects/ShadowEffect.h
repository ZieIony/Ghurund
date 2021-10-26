#pragma once

#include "ui/effects/ShadowEffect.h"

#include <wrl.h>

namespace Ghurund::UI::Direct2D {
    using Microsoft::WRL::ComPtr;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
  
    class DirectXShadowEffect:public ShadowEffect {
    private:
        ComPtr<ID2D1Effect> shadowEffect;

    public:
        DirectXShadowEffect(ID2D1DeviceContext5& deviceContext) {
            deviceContext.CreateEffect(CLSID_D2D1Shadow, &shadowEffect);
        }

        virtual void setColor(const Ghurund::UI::Color& color) {
            __super::setColor(color);
            shadowEffect->SetValue(D2D1_SHADOW_PROP_COLOR, D2D_VECTOR_4F(color.R, color.G, color.B, color.A));
        }

        virtual void setShape(Ghurund::UI::Shape* shape) {
            __super::setShape(shape);
            //shadowEffect->SetInput(0, bitmapImage);
        }

        virtual void setRadius(float radius) {
            __super::setRadius(radius);
            shadowEffect->SetValue(D2D1_SHADOW_PROP_BLUR_STANDARD_DEVIATION, radius);
        }
    };
}