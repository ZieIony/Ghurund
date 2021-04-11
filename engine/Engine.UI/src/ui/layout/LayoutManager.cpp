#include "ghuipch.h"
#include "LayoutManager.h"

namespace Ghurund::UI {
    float LayoutManager::measureMaxWidth() {
        float measuredWidth = 0;
        if (group->PreferredSize.width >= 0) {
            measuredWidth = (float)group->PreferredSize.width;
        } else {
            for (Control* c : group->Children) {
                if (c->PreferredSize.width >= 0) {
                    measuredWidth = std::max(measuredWidth, (float)c->PreferredSize.width);
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
        if (group->PreferredSize.height >= 0) {
            measuredHeight = (float)group->PreferredSize.height;
        } else {
            for (Control* c : group->Children) {
                if (c->PreferredSize.width >= 0) {
                    measuredHeight = std::max(measuredHeight, (float)c->PreferredSize.height);
                    measuredHeight = std::max(measuredHeight, c->MinSize.height);
                } else {
                    measuredHeight = std::max(measuredHeight, c->MeasuredSize.height);
                }
            }
        }
        return std::max(group->MinSize.height, measuredHeight);
    }
}