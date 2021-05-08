#pragma once

#include "core/math/Rect.h"

#include <d2d1_3.h>

struct ID2D1Geometry;

namespace Ghurund::UI {
    class Shape {
    protected:
        ID2D1Geometry* path = nullptr;
        FloatRect bounds;

    public:
        virtual ~Shape() = 0;

        inline ID2D1Geometry* getPath() {
            return path;
        }

        __declspec(property(get = getPath)) ID2D1Geometry* Path;

        inline const FloatRect& getBounds() const {
            return bounds;
        }

        virtual void setBounds(const FloatRect& bounds) {
            this->bounds = bounds;
        }

        __declspec(property(get = getBounds, put = setBounds)) const FloatRect& Bounds;
    };

    class Rect:public Shape {
    private:
        ID2D1Factory6& d2dFactory;

    public:
        Rect(ID2D1Factory6& d2dFactory):d2dFactory(d2dFactory) {}

        virtual void setBounds(const FloatRect& bounds) override;
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
    };
}