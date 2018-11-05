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
        void dispatchKeyEvent(KeyEvent &event) {

        }

        void dispatchMouseButtonEvent(MouseButtonEvent &event) {

        }

        void dispatchMouseMotionEvent(MouseMotionEvent &event) {

        }

        void dispatchMouseWheelEvent(MouseWheelEvent &event) {

        }

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