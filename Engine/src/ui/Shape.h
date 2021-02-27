#pragma once

#include "core/math/Rect.h"

struct ID2D1Geometry;

namespace Ghurund::UI {
    class Graphics2D;

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
        Graphics2D* graphics2d;

    public:
        Rect(Graphics2D& graphics2d):graphics2d(&graphics2d) {}

        virtual void setBounds(const FloatRect& bounds) override;
    };

    class RoundRect:public Shape {
    private:
        Graphics2D* graphics2d;
        float cornerRadius;

    public:
        RoundRect(Graphics2D& graphics2d, float cornerRadius = 2.0f):graphics2d(&graphics2d), cornerRadius(cornerRadius) {}

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