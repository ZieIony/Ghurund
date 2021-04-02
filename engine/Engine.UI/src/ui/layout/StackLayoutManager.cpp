#include "ghuipch.h"
#include "StackLayoutManager.h"

namespace Ghurund::UI {
    const FloatSize StackLayoutManager::measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) {
        __super::measure(group, provider, parentWidth, parentHeight);
        return { measureMaxWidth(group), measureMaxHeight(group) };
    }

    void StackLayoutManager::layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) {
        for (Control* c : group.Children) {
            if (!c->Visible)
                continue;
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = std::max(width, c->MinSize.width);
            } else if (c->PreferredSize.width >= 0){
                w = std::min((float)c->PreferredSize.width, width);
                w = std::max(w, c->MinSize.width);
            }else{
                w = std::min((float)c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = std::max(height, c->MinSize.height);
            } else if (c->PreferredSize.height >= 0) {
                h = std::min((float)c->PreferredSize.height, height);
                h = std::max(h, c->MinSize.height);
            } else {
                h = std::min((float)c->MeasuredSize.height, height);
            }

            float itx;
            if (alignment.horizontal == Alignment::Horizontal::LEFT) {
                itx = 0;
            } else if (alignment.horizontal == Alignment::Horizontal::RIGHT) {
                itx = width - w;
            } else {
                itx = (width - w) / 2;
            }

            float ity;
            if (alignment.vertical == Alignment::Vertical::TOP) {
                ity = 0;
            } else if (alignment.vertical == Alignment::Vertical::BOTTOM) {
                ity = height - h;
            } else {
                ity = (height - h) / 2;
            }

            c->layout(itx, ity, w, h);
        }
    }
}