#pragma once

#include "Mouse.h"
#include "Keyboard.h"
#include "core/Event.h"
#include "core/collection/List.h"

namespace Ghurund::Core {
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

    class EventConsumer:public EventDispatcher {
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
        Event<EventConsumer, KeyEventArgs> keyEvent = *this;
        Event<EventConsumer, MouseButtonEventArgs> mouseButtonEvent = *this;
        Event<EventConsumer, MouseMotionEventArgs> mouseMotionEvent = *this;
        Event<EventConsumer, MouseWheelEventArgs> mouseWheelEvent = *this;

        virtual ~EventConsumer() {}

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override {
            bool result = onKeyEvent(event);
            bool result2 = keyEvent(event);
            return result || result2;
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            bool result = onMouseButtonEvent(event);
            bool result2 = mouseButtonEvent(event);
            return result || result2;
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            bool result = onMouseMotionEvent(event);
            bool result2 = mouseMotionEvent(event);
            return result || result2;
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override {
            bool result = onMouseWheelEvent(event);
            bool result2 = mouseWheelEvent(event);
            return result || result2;
        }
    };
}