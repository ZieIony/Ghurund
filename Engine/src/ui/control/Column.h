#pragma once

#include "ControlGroup.h"

namespace Ghurund {
    class Column :public ControlGroup {
    public:
        HorizontalGravity horizontalGravity = HorizontalGravity::LEFT;

        virtual void measure() {
            for (Control* c : Children)
                c->measure();

            if (desiredSize.x == LayoutSize::WRAP_CONTENT) {
                measuredSize.x = 0;
                for (Control* c : Children) {
                    if (c->DesiredSize.x != LayoutSize::MATCH_PARENT)
                        measuredSize.x = std::max(measuredSize.x, c->MeasuredSize.x);
                }
            } else if (desiredSize.x == LayoutSize::MATCH_PARENT) {
                measuredSize.x = MAX_SIZE;
            } else {
                measuredSize.x = desiredSize.x;
            }

            if (desiredSize.y == LayoutSize::WRAP_CONTENT) {
                measuredSize.y = 0;
                for (Control* c : Children) {
                    if (c->DesiredSize.y != LayoutSize::MATCH_PARENT)
                        measuredSize.y += c->MeasuredSize.y;
                }
            } else if (desiredSize.y == LayoutSize::MATCH_PARENT) {
                measuredSize.y = MAX_SIZE;
            } else {
                measuredSize.y = desiredSize.y;
            }
        }

        virtual void layout(float x, float y, float width, float height) override {
            __super::layout(x, y, width, height);

            float currentY = 0.0f;
            for (Control* c : Children) {
                float w = std::min(c->MeasuredSize.x, width);
                float h = std::min(c->MeasuredSize.y, height);

                float itx;
                if (horizontalGravity == HorizontalGravity::LEFT) {
                    itx = 0;
                } else if (horizontalGravity == HorizontalGravity::RIGHT) {
                    itx = width - w;
                } else {
                    itx = (width - w) / 2;
                }

                c->layout(itx, currentY, w, h);
                currentY += c->Size.y;
            }
        }
    };
}