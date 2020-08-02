#pragma once

#include "ControlGroup.h"

namespace Ghurund {
    class Row :public ControlGroup {
    public:
        VerticalGravity verticalGravity = VerticalGravity::TOP;
   
        virtual void measure() {
            for (Control* c : Children)
                c->measure();

            if (desiredSize.x == LayoutSize::WRAP_CONTENT) {
                measuredSize.x = 0;
                for (Control* c : Children) {
                    if (c->DesiredSize.x != LayoutSize::MATCH_PARENT)
                        measuredSize.x += c->MeasuredSize.x;
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
                        measuredSize.y = std::max(measuredSize.y, c->MeasuredSize.y);
                }
            } else if (desiredSize.y == LayoutSize::MATCH_PARENT) {
                measuredSize.y = MAX_SIZE;
            } else {
                measuredSize.y = desiredSize.y;
            }
        }

        virtual void layout(float x, float y, float width, float height) override {
            __super::layout(x, y, width, height);

            float currentX = 0.0f;
            for (Control* c : Children) {
                float w = std::min(c->MeasuredSize.x, width);
                float h = std::min(c->MeasuredSize.y, height);

                float ity;
                if (verticalGravity == VerticalGravity::TOP) {
                    ity = 0;
                } else if (verticalGravity == VerticalGravity::BOTTOM) {
                    ity = height - h;
                } else {
                    ity = (height - h) / 2;
                }

                c->layout(currentX, ity, w, h);
                currentX += c->Size.x;
            }
        }
    };
}