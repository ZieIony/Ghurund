#pragma once

#include "Control.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    class Surface :public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Surface);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Surface>();

        Paint paint;

    public:
        unsigned int color;

        Surface(unsigned int color = 0x1b000000):color(color) {
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
        }

        virtual void draw(Canvas& canvas) {
            if (!color)
                return;
            paint.Color = color;
            canvas.fillRect(0, 0, size.x, size.y, paint);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Surface>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static Surface* inflate(LayoutInflater& inflater, json& json) {
            Surface* surface = ghnew Surface();
            if (json.contains("color")) {
                nlohmann::json color = json["color"];
                if (color.is_string()) {
                    std::string colorString = color;
                    surface->color = std::stoul(colorString, nullptr, 16);
                }
            }
            inflater.loadControl(surface, json);
            return surface;
        }
    };
}