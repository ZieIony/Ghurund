#pragma once

#include "ui/Shape.h"

#undef GDIPVER
#define GDIPVER     0x0110

#include <gdiplus.h>

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;

    class Shape:public Ghurund::UI::Shape {
    protected:
        Gdiplus::GraphicsPath* path = new Gdiplus::GraphicsPath();

    public:
        ~Shape();

        inline Gdiplus::GraphicsPath* getPath() {
            return path;
        }

        __declspec(property(get = getPath)) Gdiplus::GraphicsPath* Path;
    };

    class Rect:public Shape {
    public:
        virtual void setBounds(const FloatRect& bounds) override;
    };

    class RoundRect:public Shape {
    private:
        float cornerRadius;

    public:
        RoundRect(float cornerRadius = 2.0f):cornerRadius(cornerRadius) {}

        inline float getCornerRadius() const {
            return cornerRadius;
        }

        inline void setCornerRadius(float radius) {
            this->cornerRadius = radius;
        }

        __declspec(property(get = getCornerRadius, put = setCornerRadius)) float CornerRadius;

        virtual void setBounds(const FloatRect& bounds) override;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::GDI::Shape>();
}
