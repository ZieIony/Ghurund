#pragma once

#include "ControlContainer.h"

namespace Ghurund::UI {
    class Clip:public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Clip);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Clip>();

        GdiPath* path;
        float cornerRadius = 0.0f;
        Gdiplus::RectF bounds;

        inline void updatePath() {
            bounds.Width = size.width;
            bounds.Height = size.height;
            if (cornerRadius == 0) {
                path->setRect(bounds);
            } else {
                path->setRoundRect(bounds, cornerRadius);
            }
        }

    public:
        Clip() {
            path = ghnew GdiPath();
            bounds.X = 0.0f;
            bounds.Y = 0.0f;
            setCornerRadius(0.0f);
        }

        ~Clip() {
            delete path;
        }

        inline float getCornerRadius() const {
            return cornerRadius;
        }

        inline void setCornerRadius(float radius) {
            this->cornerRadius = radius;
            updatePath();
        }

        __declspec(property(get = getCornerRadius, put = setCornerRadius)) float CornerRadius;

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
            updatePath();
        }

        virtual void onDraw(Canvas& canvas) override {
            canvas.save();
            canvas.clipPath(*path);
            __super::onDraw(canvas);
            canvas.restore();
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Clip>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}