#pragma once

#include "ui/control/Border.h"
#include "ui/control/Clip.h"

namespace Ghurund::UI {
    class BorderMixin {
    protected:
        Border* border = nullptr;
        Clip* clip = nullptr;

    public:
        inline unsigned int getBorderColor() const {
            return border->Color;
        }

        inline void setBorderColor(unsigned int color) {
            border->Color = color;
        }

        __declspec(property(get = getBorderColor, put = setBorderColor)) unsigned int BorderColor;

        inline Shape* getBorderShape() const {
            return border->Shape;
        }

        inline void setBorderShape(Shape* shape) {
            border->Shape = shape;
            if (clip)
                clip->Shape = shape;
        }

        __declspec(property(get = getBorderShape, put = setBorderShape)) Shape* BorderShape;

        inline float getBorderThickness() const {
            return border->Thickness;
        }

        inline void setBorderThickness(float thickness) {
            border->Thickness = thickness;
        }

        __declspec(property(get = getBorderThickness, put = setBorderThickness)) float BorderThickness;
    };

    class BorderLayoutMixin {
    protected:
        Border* border;
        Clip* clip;

    public:
        BorderLayoutMixin() {
            border = ghnew Ghurund::UI::Border();
            clip = ghnew Ghurund::UI::Clip();
        }

        ~BorderLayoutMixin() {
            border->release();
            clip->release();
        }

        inline Border* getBorder() {
            return border;
        }

        __declspec(property(get = getBorder)) Border* Border;

        inline Clip* getClip() {
            return clip;
        }

        __declspec(property(get = getClip)) Clip* Clip;
    };
}