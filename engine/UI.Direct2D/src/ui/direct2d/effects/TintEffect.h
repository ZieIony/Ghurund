#pragma once

#include "ui/effects/TintEffect.h"

#include <d2d1effects_2.h>

namespace Ghurund::UI::Direct2D {
    class DirectXTintEffect:public TintEffect {
    private:
        ComPtr<ID2D1Effect> tintEffect;

    public:
        DirectXTintEffect(ID2D1DeviceContext5& deviceContext) {
            deviceContext.CreateEffect(CLSID_D2D1Tint, &tintEffect);
        }

        virtual void setColor(const Ghurund::UI::Color& color) {
            __super::setColor(color);
            tintEffect->SetValue(D2D1_TINT_PROP_COLOR, D2D_VECTOR_4F(color.R, color.G, color.B, color.A));
        }
    };
}