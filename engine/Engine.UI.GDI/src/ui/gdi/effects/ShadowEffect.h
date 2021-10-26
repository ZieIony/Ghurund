#pragma once

#include "ui/effects/ShadowEffect.h"

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
  
    class GDIShadowEffect:public ShadowEffect {
    public:
        virtual void setColor(const Ghurund::UI::Color& color) {
            __super::setColor(color);
        }

        virtual void setShape(Ghurund::UI::Shape* shape) {
            __super::setShape(shape);
        }

        virtual void setRadius(float radius) {
            __super::setRadius(radius);
        }
    };
}