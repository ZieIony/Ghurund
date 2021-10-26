#include "ghuipch.h"
#include "StackLayoutManager.h"

namespace Ghurund::UI {
    const FloatSize StackLayoutManager::measure(float parentWidth, float parentHeight) {
        __super::measure(parentWidth, parentHeight);
        return { measureMaxWidth(), measureMaxHeight() };
    }

    void StackLayoutManager::layout(float x, float y, float width, float height) {
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = std::max(width, c->MinSize.width);
            } else if (c->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
                w = std::min(c->PreferredSize.width.Value, width);
                w = std::max(w, c->MinSize.width);
            } else {
                w = std::min((float)c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = std::max(height, c->MinSize.height);
            } else if (c->PreferredSize.height.Type == PreferredSize::Type::PIXELS) {
                h = std::min(c->PreferredSize.height.Value, height);
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

            if (group->RoundToPixelsEnabled) {
                itx = round(itx);
                ity = round(ity);
                w = round(w);
                h = round(h);
            }
            c->layout(itx, ity, w, h);
        }
    }
}