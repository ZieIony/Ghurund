#include "Stack.h"

namespace Ghurund::UI {
    void Stack::onLayout(float x, float y, float width, float height) {
        for (Control* c : Children) {
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = width;
            } else {
                w = std::min((float)c->MeasuredSize.x, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = height;
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

            float ity;
            if (gravity.vertical == Gravity::Vertical::TOP) {
                ity = 0;
            } else if (gravity.vertical == Gravity::Vertical::BOTTOM) {
                ity = height - h;
            } else {
                ity = (height - h) / 2;
            }

            c->layout(itx, ity, w, h);
        }
    }

    Stack* Stack::inflate(LayoutInflater& inflater, json& json) {
        Stack* stack = ghnew Stack();
        inflater.loadChildren(stack, json);
        inflater.loadControl(stack, json);
        inflater.loadGravity(stack, json);
        return stack;
    }
}