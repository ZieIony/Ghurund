#pragma once

#include "core/Timer.h"
#include "Mouse.h"
#include "collection/List.h"
#include "Keyboard.h"
#include "Windowsx.h"

namespace Ghurund {
    class EventDispatcher {
    public:
        virtual ~EventDispatcher() {}

        virtual bool dispatchKeyEvent(KeyEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseButtonEvent(MouseButtonEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseMotionEvent(MouseMotionEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseWheelEvent(MouseWheelEventArgs& event) {
            return false;
        }
    };

    class EventConsumer :public EventDispatcher {
    protected:
        virtual bool onKeyEvent(KeyEventArgs& event) {
            return false;
        }

        virtual bool onMouseButtonEvent(MouseButtonEventArgs& event) {
            return false;
        }

        virtual bool onMouseMouseMotionEvent(MouseMotionEventArgs& event) {
            return false;
        }

        virtual bool onMouseWheelEvent(MouseWheelEventArgs& event) {
            return false;
        }

    public:
        virtual ~EventConsumer() {}

        virtual bool dispatchKeyEvent(KeyEventArgs& event) {
            return onKeyEvent(event);
        }

        virtual bool dispatchMouseButtonEvent(MouseButtonEventArgs& event) {
            return onMouseButtonEvent(event);
        }

        virtual bool dispatchMouseMotionEvent(MouseMotionEventArgs& event) {
            return onMouseMouseMotionEvent(event);
        }

        virtual bool dispatchMouseWheelEvent(MouseWheelEventArgs& event) {
            return onMouseWheelEvent(event);
        }
    };
}