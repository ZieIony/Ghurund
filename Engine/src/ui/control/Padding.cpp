#include "Padding.h"

namespace Ghurund::UI {
    void Padding::measure() {
        if (Child) {
            if (PreferredSize.width == PreferredSize::Width::WRAP || PreferredSize.width == PreferredSize::Width::FILL) {
                Child->PreferredSize.width = PreferredSize.width;
            } else {
                Child->PreferredSize.width = PreferredSize::Width((float)PreferredSize.width - left - right);
            }
            if (PreferredSize.height == PreferredSize::Height::WRAP || PreferredSize.height == PreferredSize::Height::FILL) {
                Child->PreferredSize.height = PreferredSize.height;
            } else {
                Child->PreferredSize.height = PreferredSize::Height((float)PreferredSize.height - top - bottom);
            }
            Child->measure();
        }

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.x = left + right;
            if (Child)
                measuredSize.x += (float)Child->MeasuredSize.x;
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.x = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.y = top + bottom;
            if (Child)
                measuredSize.y += (float)Child->MeasuredSize.y;
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.y = (float)preferredSize.height;
        }
    }

    Padding* Padding::inflate(LayoutInflater& inflater, json& json) {
        Padding* padding = ghnew Padding();
        if (json.contains("left")) {
            nlohmann::json left = json["left"];
            if (left.is_number())
                padding->left = left;
        }
        if (json.contains("right")) {
            nlohmann::json right = json["right"];
            if (right.is_number())
                padding->right = right;
        }
        if (json.contains("top")) {
            nlohmann::json top = json["top"];
            if (top.is_number())
                padding->top = top;
        }
        if (json.contains("bottom")) {
            nlohmann::json bottom = json["bottom"];
            if (bottom.is_number())
                padding->bottom = bottom;
        }
        inflater.loadChild(padding, json);
        inflater.loadControl(padding, json);
        return padding;
    }
}