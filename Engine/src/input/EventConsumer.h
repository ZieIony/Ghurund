#pragma once

#include "application/Timer.h"
#include "Mouse.h"
#include "core/collection/List.h"
#include "Keyboard.h"
#include "Windowsx.h"

namespace Ghurund {
    class EventDispatcher {
    public:
        virtual ~EventDispatcher() {}

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            return false;
        }
    };

    class EventConsumer :public EventDispatcher {
    protected:
        virtual bool onKeyEvent(const KeyEventArgs& event) {
            return false;
        }

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) {
            return false;
        }

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) {
            return false;
        }

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) {
            return false;
        }

    public:
        virtual ~EventConsumer() {}

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) {
            return onKeyEvent(event);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            return onMouseButtonEvent(event);
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return onMouseMotionEvent(event);
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            return onMouseWheelEvent(event);
        }
    };
}