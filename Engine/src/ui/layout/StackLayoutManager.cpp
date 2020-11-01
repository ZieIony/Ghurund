#include "StackLayoutManager.h"

namespace Ghurund::UI {
    FloatSize StackLayoutManager::measure(ControlGroup& group, float parentWidth, float parentHeight) {
        __super::measure(group, parentWidth, parentHeight);
        return { measureMaxWidth(group), measureMaxHeight(group) };
    }

    void StackLayoutManager::layout(ControlGroup& group, float x, float y, float width, float height) {
        for (Control* c : group.Children) {
            if (!c->Visible)
                continue;
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = width;
            } else {
                w = std::min((float)c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = height;
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