#pragma once

#include "core/Event.h"
#include "gamepad/GamepadButtonEventArgs.h"
#include "gamepad/GamepadStickEventArgs.h"
#include "gamepad/GamepadTriggerEventArgs.h"
#include "keyboard/KeyEventArgs.h"
#include "mouse/MouseButtonEventArgs.h"
#include "mouse/MouseMotionEventArgs.h"
#include "mouse/MouseWheelEventArgs.h"

namespace Ghurund::Core {
    class EventConsumer {
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
        Event<EventConsumer, bool, GamepadButtonEventArgs> gamepadButtonEvent = *this;
        Event<EventConsumer, bool, GamepadStickEventArgs> gamepadStickEvent = *this;
        Event<EventConsumer, bool, GamepadTriggerEventArgs> gamepadTriggerEvent = *this;
        Event<EventConsumer, bool, KeyEventArgs> keyEvent = *this;
        Event<EventConsumer, bool, MouseButtonEventArgs> mouseButtonEvent = *this;
        Event<EventConsumer, bool, MouseMotionEventArgs> mouseMotionEvent = *this;
        Event<EventConsumer, bool, MouseWheelEventArgs> mouseWheelEvent = *this;

        inline bool dispatchKeyEvent(const KeyEventArgs& event) {
            bool result = onKeyEvent(event);
            bool result2 = keyEvent(event);
            return result || result2;
        }

        inline bool dispatchGamepadButtonEvent(const GamepadButtonEventArgs& event) {
            bool result = onGamepadButtonEvent(event);
            bool result2 = gamepadButtonEvent(event);
            return result || result2;
        }

        inline bool dispatchGamepadStickEvent(const GamepadStickEventArgs& event) {
            bool result = onGamepadStickEvent(event);
            bool result2 = gamepadStickEvent(event);
            return result || result2;
        }

        inline bool dispatchGamepadTriggerEvent(const GamepadTriggerEventArgs& event) {
            bool result = onGamepadTriggerEvent(event);
            bool result2 = gamepadTriggerEvent(event);
            return result || result2;
        }

        inline bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            bool result = onMouseButtonEvent(event);
            bool result2 = mouseButtonEvent(event);
            return result || result2;
        }

        inline bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            bool result = onMouseMotionEvent(event);
            bool result2 = mouseMotionEvent(event);
            return result || result2;
        }

        inline bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            bool result = onMouseWheelEvent(event);
            bool result2 = mouseWheelEvent(event);
            return result || result2;
        }
    };
}