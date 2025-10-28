#pragma once

#include "core/Event.h"
#include "EventDispatcher.h"
#include "gamepad/GamepadButtonEventArgs.h"
#include "gamepad/GamepadStickEventArgs.h"
#include "gamepad/GamepadTriggerEventArgs.h"

namespace Ghurund::Core {
    class EventConsumer:public EventDispatcher {
    protected:
        virtual bool onGamepadButtonEvent(const GamepadButtonEventArgs& event) {
            return false;
        }

        virtual bool onGamepadStickEvent(const GamepadStickEventArgs& event) {
            return false;
        }

        virtual bool onGamepadTriggerEvent(const GamepadTriggerEventArgs& event) {
            return false;
        }

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
        Event<EventConsumer, GamepadButtonEventArgs> gamepadButtonEvent = *this;
        Event<EventConsumer, GamepadStickEventArgs> gamepadStickEvent = *this;
        Event<EventConsumer, GamepadTriggerEventArgs> gamepadTriggerEvent = *this;
        Event<EventConsumer, KeyEventArgs> keyEvent = *this;
        Event<EventConsumer, MouseButtonEventArgs> mouseButtonEvent = *this;
        Event<EventConsumer, MouseMotionEventArgs> mouseMotionEvent = *this;
        Event<EventConsumer, MouseWheelEventArgs> mouseWheelEvent = *this;

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override {
            bool result = onKeyEvent(event);
            bool result2 = keyEvent(event);
            return result || result2;
        }

        virtual bool dispatchGamepadButtonEvent(const GamepadButtonEventArgs& event) override {
            bool result = onGamepadButtonEvent(event);
            bool result2 = gamepadButtonEvent(event);
            return result || result2;
        }

        virtual bool dispatchGamepadStickEvent(const GamepadStickEventArgs& event) override {
            bool result = onGamepadStickEvent(event);
            bool result2 = gamepadStickEvent(event);
            return result || result2;
        }

        virtual bool dispatchGamepadTriggerEvent(const GamepadTriggerEventArgs& event) override {
            bool result = onGamepadTriggerEvent(event);
            bool result2 = gamepadTriggerEvent(event);
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