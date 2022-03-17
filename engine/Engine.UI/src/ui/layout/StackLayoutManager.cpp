#include "ghuipch.h"
#include "StackLayoutManager.h"

namespace Ghurund::UI {
    const FloatSize StackLayoutManager::measure(float parentWidth, float parentHeight) {
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            if (c->PreferredSize.width.Type == PreferredSize::Type::FILL && group->PreferredSize.width.Type == PreferredSize::Type::WRAP ||
                c->PreferredSize.height.Type == PreferredSize::Type::FILL && group->PreferredSize.height.Type == PreferredSize::Type::WRAP)
                continue;
            c->measure(parentWidth, parentHeight);
        }
        float width;
        if (group->PreferredSize.width.Type == PreferredSize::Type::WRAP) {
            width = group->resolveWidth(measureMaxWidth(), parentWidth, parentHeight);
        } else {
            width = group->resolveWidth(0, parentWidth, parentHeight);
        }
        float height;
        if (group->PreferredSize.height.Type == PreferredSize::Type::WRAP) {
            height = group->resolveHeight(measureMaxHeight(), parentHeight);
        } else {
            height = group->resolveHeight(0, parentWidth, parentHeight);
        }
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            if (c->PreferredSize.width.Type == PreferredSize::Type::FILL && group->PreferredSize.width.Type == PreferredSize::Type::WRAP ||
                c->PreferredSize.height.Type == PreferredSize::Type::FILL && group->PreferredSize.height.Type == PreferredSize::Type::WRAP)
                c->measure(width, height);
        }
        return { width, height };
    }

    void StackLayoutManager::layout(float x, float y, float width, float height) {
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = std::max(width, c->MinSize.Width);
            } else if (c->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
                w = std::min(c->PreferredSize.width.Value, width);
                w = std::max(w, c->MinSize.Width);
            } else {
                w = std::min((float)c->MeasuredSize.Width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = std::max(height, c->MinSize.Height);
            } else if (c->PreferredSize.height.Type == PreferredSize::Type::PIXELS) {
                h = std::min(c->PreferredSize.height.Value, height);
                h = std::max(h, c->MinSize.Height);
            } else {
                h = std::min((float)c->MeasuredSize.Height, height);
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