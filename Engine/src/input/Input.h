#pragma once

#include "core/Timer.h"
#include "Mouse.h"
#include "collection/List.h"
#include "Keyboard.h"

namespace Ghurund {
    class EventConsumer {
    public:
        virtual bool onKeyEvent(KeyEvent &event) {
            return false;
        }

        virtual bool onMouseButtonEvent(MouseButtonEvent &event) {
            return false;
        }

        virtual bool onMouseMouseMotionEvent(MouseMotionEvent &event) {
            return false;
        }

        virtual bool onMouseWheelEvent(MouseWheelEvent &event) {
            return false;
        }

        virtual bool dispatchKeyEvent(KeyEvent &event) {
            return onKeyEvent(event);
        }

        virtual bool dispatchMouseButtonEvent(MouseButtonEvent &event) {
            return onMouseButtonEvent(event);
        }

        virtual bool dispatchMouseMotionEvent(MouseMotionEvent &event) {
            return onMouseMouseMotionEvent(event);
        }

        virtual bool dispatchMouseWheelEvent(MouseWheelEvent &event) {
            return onMouseWheelEvent(event);
        }
    };

    class Input {
    private:
        List<KeyEvent*> keyEvents;
        /*List<MouseButtonEvent> mouseButtonEvents;
        List<MouseMotionEvent> mouseMotionEvents;
        List<MouseWheelEvent> mouseWheelEvents;*/

    public:
        void dispatchKeyEvent(KeyEvent &event) {
            keyEvents.add(ghnew KeyEvent(event));
        }

        void dispatchMouseButtonEvent(MouseButtonEvent &event) {

        }

        void dispatchMouseMotionEvent(MouseMotionEvent &event) {

        }

        void dispatchMouseWheelEvent(MouseWheelEvent &event) {

        }

        void update(float deltaTime) {}

        void dispatchEvents(EventConsumer &consumer) {
            for(size_t i = 0; i<keyEvents.Size;) {
                bool consumed = consumer.dispatchKeyEvent(*keyEvents[i]);
                if(consumed) {
                    delete keyEvents[i];
                    keyEvents.removeAtKeepOrder(i);
                } else {
                    i++;
                }
            }
        }

        void clearEvents() {
            keyEvents.clear();
     /*       mouseButtonEvents.clear();
            mouseMotionEvents.clear();
            mouseWheelEvents.clear();*/
        }
    };
}