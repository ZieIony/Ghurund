#pragma once

#include "ui/Graphics2D.h"

namespace Ghurund::UI {
    class Shape {
    protected:
        ComPtr<ID2D1PathGeometry> path;
        D2D_RECT_F bounds;

    public:
        virtual ~Shape() = 0 {}

        inline ID2D1PathGeometry* getPath() {
            return path.Get();
        }

        __declspec(property(get = getPath)) ID2D1PathGeometry* Path;

        inline const D2D_RECT_F& getBounds() const {
            return bounds;
        }

        virtual void setBounds(const D2D_RECT_F& bounds) {
            this->bounds = bounds;
        }

        __declspec(property(get = getBounds, put = setBounds)) const D2D_RECT_F& Bounds;
    };

    class Rect:public Shape {
    private:
        Graphics2D* graphics2d;

    public:
        Rect(Graphics2D& graphics2d):graphics2d(&graphics2d) {}

        virtual void setBounds(const D2D_RECT_F& bounds) override;
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

        virtual void setBounds(const D2D_RECT_F& bounds) override;
    };
}