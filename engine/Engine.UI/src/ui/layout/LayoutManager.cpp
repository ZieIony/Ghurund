#include "ghuipch.h"
#include "LayoutManager.h"

namespace Ghurund::UI {
    float LayoutManager::measureMaxWidth() {
        float measuredWidth = 0;
        if (group->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
            measuredWidth = group->PreferredSize.width.Value;
        } else {
            for (Control* c : group->Children) {
                if (c->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
                    measuredWidth = std::max(measuredWidth, c->PreferredSize.width.Value);
                    measuredWidth = std::max(measuredWidth, c->MinSize.width);
                } else {
                    measuredWidth = std::max(measuredWidth, c->MeasuredSize.width);
                }
            }
        }
        return std::max(group->MinSize.width, measuredWidth);
    }

    float LayoutManager::measureMaxHeight() {
        float measuredHeight = 0;
        if (group->PreferredSize.height.Type == PreferredSize::Type::PIXELS) {
            measuredHeight = group->PreferredSize.height.Value;
        } else {
            for (Control* c : group->Children) {
                if (c->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
                    measuredHeight = std::max(measuredHeight, c->PreferredSize.height.Value);
                    measuredHeight = std::max(measuredHeight, c->MinSize.height);
                } else {
                    measuredHeight = std::max(measuredHeight, c->MeasuredSize.height);
                }
            }
        }
        return std::max(group->MinSize.height, measuredHeight);
    }
}