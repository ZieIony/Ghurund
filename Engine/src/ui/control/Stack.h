#pragma once

#include "ControlGroup.h"

#include <algorithm>

namespace Ghurund {
    class Stack : public ControlGroup {
    private:
        Gravity gravity;

    public:
        inline Gravity& getGravity() {
            return gravity;
        }

        inline void setGravity(const Gravity& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Gravity& Gravity;

        virtual void measure() {
            __super::measure();

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

            for (Control* c : Children){
                float w = std::min(c->MeasuredSize.x, width);
                float h = std::min(c->MeasuredSize.y, height);

                float itx;
                if (gravity.horizontal == HorizontalGravity::LEFT) {
                    itx = 0;
                } else if (gravity.horizontal == HorizontalGravity::RIGHT) {
                    itx = width - w;
                } else {
                    itx = (width - w) / 2;
                }

                float ity;
                if (gravity.vertical == VerticalGravity::TOP) {
                    ity = 0;
                } else if (gravity.vertical == VerticalGravity::BOTTOM) {
                    ity = height - h;
                } else {
                    ity = (height - h) / 2;
                }

                c->layout(itx, ity, w, h);
            }
        }
    };
}