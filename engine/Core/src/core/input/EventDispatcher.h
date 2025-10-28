#pragma once

#include "gamepad/GamepadButtonEventArgs.h"
#include "gamepad/GamepadStickEventArgs.h"
#include "gamepad/GamepadTriggerEventArgs.h"
#include "keyboard/KeyEventArgs.h"
#include "mouse/MouseButtonEventArgs.h"
#include "mouse/MouseMotionEventArgs.h"
#include "mouse/MouseWheelEventArgs.h"

namespace Ghurund::Core {
    class EventDispatcher:public Noncopyable {
    public:
        virtual bool dispatchGamepadButtonEvent(const GamepadButtonEventArgs& event) {
            return false;
        }

        virtual bool dispatchGamepadStickEvent(const GamepadStickEventArgs& event) {
            return false;
        }

        virtual bool dispatchGamepadTriggerEvent(const GamepadTriggerEventArgs& event) {
            return false;
        }

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
}