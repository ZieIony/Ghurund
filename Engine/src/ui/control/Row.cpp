#include "Row.h"

namespace Ghurund::UI {
    void Row::measure() {
        contentWidth = 0.0f;
        spreadCount = 0;
        for (Control* c : Children) {
            c->measure();
            if (c->PreferredSize.width != PreferredSize::Width::FILL) {
                contentWidth += (float)c->MeasuredSize.x;
            } else {
                spreadCount++;
            }
        }

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.x = 0;
            for (Control* c : Children) {
                if (c->PreferredSize.width != PreferredSize::Width::FILL)
                    measuredSize.x += (float)c->MeasuredSize.x;
            }
        } else if (preferredSize.width == PreferredSize::Width::FILL) {
            measuredSize.x = 0;
        } else {
            measuredSize.x = (float)preferredSize.width;
        }

        measureMaxHeight();
    }

    void Row::layout(float x, float y, float width, float height) {
        __super::layout(x, y, width, height);
        
        float spaceLeft = std::max(0.0f, width - contentWidth);
        float currentX;
        if (gravity.horizontal == Gravity::Horizontal::LEFT || spreadCount > 0) {
            currentX = 0.0f;
        } else if (gravity.horizontal == Gravity::Horizontal::CENTER) {
            currentX = spaceLeft / 2.0f;
        } else {
            currentX = spaceLeft;
        }

        for (Control* c : Children) {
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = spaceLeft / spreadCount;
            } else {
                w = std::min(c->MeasuredSize.x, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = height;
            } else {
                h = std::min((float)c->MeasuredSize.y, height);
            }

            float ity;
            if (gravity.vertical == Gravity::Vertical::TOP) {
                ity = 0;
            } else if (gravity.vertical == Gravity::Vertical::BOTTOM) {
                ity = height - h;
            } else {
                ity = (height - h) / 2;
            }

            c->layout(currentX, ity, w, h);
            currentX += w;
        }
    }
}