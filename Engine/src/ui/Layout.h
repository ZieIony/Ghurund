#pragma once

#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "Control.h"
#include "collection/List.h"

namespace Ghurund {
    class Layout:public Control {
    private:
        List<Control*> children;

    public:
        void dispatchOnSizeChangedEvent() {
            for(Control *c:children) {

            }
        }

        virtual void setSize(float width, float height) override {
            Control::setSize(width, height);
            dispatchOnSizeChangedEvent();
        }

        void add(Control &control) {
            children.add(&control);
        }
    };
}