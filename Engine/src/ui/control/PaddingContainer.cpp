#include "PaddingContainer.h"

namespace Ghurund::UI {
    void PaddingContainer::measure() {
        if (Child) {
            if (PreferredSize.width == PreferredSize::Width::WRAP || PreferredSize.width == PreferredSize::Width::FILL) {
                Child->PreferredSize.width = PreferredSize.width;
            } else {
                Child->PreferredSize.width = PreferredSize::Width((float)PreferredSize.width - padding.left - padding.right);
            }
            if (PreferredSize.height == PreferredSize::Height::WRAP || PreferredSize.height == PreferredSize::Height::FILL) {
                Child->PreferredSize.height = PreferredSize.height;
            } else {
                Child->PreferredSize.height = PreferredSize::Height((float)PreferredSize.height - padding.top - padding.bottom);
            }
            Child->measure();
        }

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.x = padding.left + padding.right;
            if (Child)
                measuredSize.x += (float)Child->MeasuredSize.x;
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.x = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.y = padding.top + padding.bottom;
            if (Child)
                measuredSize.y += (float)Child->MeasuredSize.y;
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.y = (float)preferredSize.height;
        }
    }

    PaddingContainer* PaddingContainer::inflate(LayoutInflater& inflater, json& json) {
        PaddingContainer* padding = ghnew PaddingContainer();
        if (json.contains("all")) {
            nlohmann::json all = json["all"];
            if (all.is_number())
                padding->padding.All = all;
        }
        if (json.contains("vertical")) {
            nlohmann::json vertical = json["vertical"];
            if (vertical.is_number())
                padding->padding.Vertical = vertical;
        }
        if (json.contains("horizontal")) {
            nlohmann::json horizontal = json["horizontal"];
            if (horizontal.is_number())
                padding->padding.Horizontal = horizontal;
        }
        if (json.contains("left")) {
            nlohmann::json left = json["left"];
            if (left.is_number())
                padding->padding.left = left;
        }
        if (json.contains("right")) {
            nlohmann::json right = json["right"];
            if (right.is_number())
                padding->padding.right = right;
        }
        if (json.contains("top")) {
            nlohmann::json top = json["top"];
            if (top.is_number())
                padding->padding.top = top;
        }
        if (json.contains("bottom")) {
            nlohmann::json bottom = json["bottom"];
            if (bottom.is_number())
                padding->padding.bottom = bottom;
        }
        inflater.loadChild(padding, json);
        inflater.loadControl(padding, json);
        return padding;
    }
}