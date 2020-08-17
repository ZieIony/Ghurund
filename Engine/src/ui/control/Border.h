#pragma once

#include "Control.h"
#include "ui/layout/LayoutInflater.h"
#include "ui/gdi/GdiPath.h"

namespace Ghurund::UI {
    class Border : public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Border);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Border>();

        unsigned int color = 0x1f000000;
        GdiPath* path;
        float cornerRadius = 0.0f, thickness = 1.0f;
        Gdiplus::RectF bounds;
        Paint paint;

        inline void updatePath() {
            bounds.X = 0;
            bounds.Y = 0;
            bounds.Width = size.x - 1;
            bounds.Height = size.y - 1;
            if (cornerRadius == 0) {
                path->setRect(bounds);
            } else {
                path->setRoundRect(bounds, cornerRadius);
            }
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

        virtual void layout(float x, float y, float width, float height) override {
            __super::layout(x, y, width, height);
            updatePath();
        }

        virtual void draw(Canvas& canvas) override {
            paint.setThickness(thickness);
            paint.setColor(color);
            canvas.drawPath(*path, paint);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Border>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(Control::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static Border* inflate(LayoutInflater& inflater, json& json) {
            Border* border = ghnew Border();
            if (json.contains("color")) {
                nlohmann::json color = json["color"];
                if (color.is_string()) {
                    std::string colorString = color;
                    border->color = std::stoul(colorString, nullptr, 16);
                }
            }
            inflater.loadControl(border, json);
            return border;
        }
    };
}