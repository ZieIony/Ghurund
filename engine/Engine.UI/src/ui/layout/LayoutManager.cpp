#include "ghuipch.h"
#include "LayoutManager.h"

namespace Ghurund::UI {
    float LayoutManager::measureMaxWidth() {
        float measuredWidth = 0;
        for (Control* c : group->Children)
            measuredWidth = std::max(measuredWidth, c->MeasuredSize.Width);
        return measuredWidth;
    }

    float LayoutManager::measureMaxHeight() {
        float measuredHeight = 0;
        for (Control* c : group->Children)
            measuredHeight = std::max(measuredHeight, c->MeasuredSize.Height);
        return measuredHeight;
    }
}