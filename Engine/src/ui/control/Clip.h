#pragma once

#include "ControlContainer.h"

namespace Ghurund::UI {
    class Clip:public ControlContainer {
    private:
        GdiPath* path;
        float cornerRadius = 0.0f;
        Gdiplus::RectF bounds;

        inline void updatePath() {
            bounds.Width = Size.width - 1;
            bounds.Height = Size.height - 1;
            if (cornerRadius == 0) {
                path->setRect(bounds);
            } else {
                path->setRoundRect(bounds, cornerRadius);
            }
        }

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<Clip>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Clip))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        Clip() {
            path = ghnew GdiPath();
            bounds.X = -0.5f;
            bounds.Y = -0.5f;
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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}