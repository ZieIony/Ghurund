#pragma once

#include "Control.h"
#include "ui/gdi/GdiPath.h"

namespace Ghurund::UI {
    class Border : public Control {
    private:
        unsigned int color = 0x1f000000;
        GdiPath* path;
        float cornerRadius = 0.0f, thickness = 1.0f;
        Gdiplus::RectF bounds;
        Paint paint;

        inline void updatePath() {
            bounds.X = 0;
            bounds.Y = 0;
            bounds.Width = Size.width - 1;
            bounds.Height = Size.height - 1;
            if (cornerRadius == 0) {
                path->setRect(bounds);
            } else {
                path->setRoundRect(bounds, cornerRadius);
            }
        }

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<Border>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Border))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        Border(unsigned int color = 0x1f000000):color(color) {
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
            path = ghnew GdiPath();
            setCornerRadius(0.0f);
        }

        ~Border() {
            delete path;
        }

        inline unsigned int getColor() const {
            return color;
        }

        inline void setColor(unsigned int color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) unsigned int Color;

        inline float getCornerRadius() const {
            return cornerRadius;
        }

        inline void setCornerRadius(float radius) {
            this->cornerRadius = radius;
            updatePath();
        }

        __declspec(property(get = getCornerRadius, put = setCornerRadius)) float CornerRadius;

        inline float getThickness() const {
            return thickness;
        }

        inline void setThickness(float thickness) {
            this->thickness = thickness;
        }

        __declspec(property(get = getThickness, put = setThickness)) float Thickness;

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
            updatePath();
        }

        virtual void onDraw(Canvas& canvas) override {
            if (!color || thickness < 0.1f)
                return;
            paint.setThickness(thickness);
            paint.setColor(color);
            canvas.drawPath(*path, paint);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}