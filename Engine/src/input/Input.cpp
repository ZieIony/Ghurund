#include "Input.h"

namespace Ghurund {
    bool Input::dispatchEvent(SystemMessage& message, EventDispatcher& consumer) {
        if (message.code == WM_KEYDOWN) {
            keys[message.wParam] = true;
            return consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::DOWN, (int)message.wParam, message.time));
        } else if (message.code == WM_KEYUP) {
            keys[message.wParam] = false;
            return consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::UP, (int)message.wParam, message.time));
        } else if (message.code == WM_LBUTTONDOWN) {
            return consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(MouseAction::DOWN, MouseButton::LEFT, message.time));
        } else if (message.code == WM_LBUTTONUP) {
            return consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(MouseAction::UP, MouseButton::LEFT, message.time));
        } else if (message.code == WM_MBUTTONDOWN) {
            return consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(MouseAction::DOWN, MouseButton::MIDDLE, message.time));
        } else if (message.code == WM_MBUTTONUP) {
            return consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(MouseAction::UP, MouseButton::MIDDLE, message.time));
        } else if (message.code == WM_RBUTTONDOWN) {
            return consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(MouseAction::DOWN, MouseButton::RIGHT, message.time));
        } else if (message.code == WM_RBUTTONUP) {
            return consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(MouseAction::UP, MouseButton::RIGHT, message.time));
        } else if (message.code == WM_MOUSEMOVE) {
            int x2 = GET_X_LPARAM(message.lParam);
            int y2 = GET_Y_LPARAM(message.lParam);
            bool result = consumer.dispatchMouseMotionEvent(MouseMotionEventArgs(XMINT2(x2 - mousePos.x, y2 - mousePos.y), message.time));
            mousePos.x = x2;
            mousePos.y = y2;
            return result;
        } else if (message.code == WM_MOUSEWHEEL) {
            return consumer.dispatchMouseWheelEvent(MouseWheelEventArgs(MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(message.wParam), message.time));
        } else if (message.code == WM_MOUSEHWHEEL) {
            return consumer.dispatchMouseWheelEvent(MouseWheelEventArgs(MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(message.wParam), message.time));
        }
        return false;	// shouldn't ever happen
    }
}