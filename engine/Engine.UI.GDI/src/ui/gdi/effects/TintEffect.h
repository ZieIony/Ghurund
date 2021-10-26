#pragma once

#include "ui/effects/TintEffect.h"

#include <d2d1effects_2.h>

namespace Ghurund::UI::GDI {
    class GDITintEffect:public TintEffect {
    public:
        virtual void setColor(const Ghurund::UI::Color& color) {
            __super::setColor(color);
        }
    };
}