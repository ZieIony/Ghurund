#pragma once

#include "ui/Shape.h"

#include <d2d1_3.h>

struct ID2D1Geometry;

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class Shape:public Ghurund::UI::Shape {
    protected:
        ID2D1Geometry* path = nullptr;

    public:
        ~Shape();

        inline ID2D1Geometry* getPath() {
            return path;
        }

        __declspec(property(get = getPath)) ID2D1Geometry* Path;
    };

    class Rect:public Shape {
    private:
        ID2D1Factory6& d2dFactory;

    public:
        Rect(ID2D1Factory6& d2dFactory):d2dFactory(d2dFactory) {}

        virtual void setBounds(const FloatRect& bounds) override;

        virtual Rect* clone() const override {
            auto rect = ghnew Rect(d2dFactory);
            rect->Bounds = Bounds;
            return rect;
        }
    };

    class RoundRect:public Shape {
    private:
        ID2D1Factory6& d2dFactory;
        float cornerRadius;

    public:
        RoundRect(ID2D1Factory6& d2dFactory, float cornerRadius = 2.0f):d2dFactory(d2dFactory), cornerRadius(cornerRadius) {}

        inline float getCornerRadius() const {
            return cornerRadius;
        }

        inline void setCornerRadius(float radius) {
            this->cornerRadius = radius;
        }

        __declspec(property(get = getCornerRadius, put = setCornerRadius)) float CornerRadius;

        virtual void setBounds(const FloatRect& bounds) override;

        virtual RoundRect* clone() const override {
            auto rect = ghnew RoundRect(d2dFactory);
            rect->Bounds = Bounds;
            rect->CornerRadius = CornerRadius;
            return rect;
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Direct2D::Shape>();
}
