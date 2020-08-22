#include "Column.h"

namespace Ghurund::UI {
    void Column::onMeasure() {
        contentHeight = 0.0f;
        spreadCount = 0;
        for (Control* c : Children) {
            c->measure();
            if (c->PreferredSize.height != PreferredSize::Height::FILL) {
                contentHeight += (float)c->MeasuredSize.y;
            } else {
                spreadCount++;
            }
        }

        measureMaxWidth();

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.y = 0;
            for (Control* c : Children) {
                if (c->PreferredSize.height != PreferredSize::Height::FILL)
                    measuredSize.y += (float)c->MeasuredSize.y;
            }
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.y = (float)preferredSize.height;
        }
    }

    void Column::onLayout(float x, float y, float width, float height) {
        float spaceLeft = std::max(0.0f, height - contentHeight);
        float currentY = 0.0f;
        if (gravity.vertical == Gravity::Vertical::TOP || spreadCount > 0) {
            currentY = 0.0f;
        } else if (gravity.vertical == Gravity::Vertical::CENTER) {
            currentY = spaceLeft / 2.0f;
        } else {
            currentY = spaceLeft;
        }

        for (Control* c : Children) {
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = width;
            } else {
                w = std::min((float)c->MeasuredSize.x, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = spaceLeft / spreadCount;
            } else {
                h = std::min((float)c->MeasuredSize.y, height);
            }

            float itx;
            if (gravity.horizontal == Gravity::Horizontal::LEFT) {
                itx = 0;
            } else if (gravity.horizontal == Gravity::Horizontal::RIGHT) {
                itx = width - w;
            } else {
                itx = (width - w) / 2;
            }

            c->layout(itx, currentY, w, h);
            currentY += h;
        }
    }
}