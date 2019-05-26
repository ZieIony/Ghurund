#pragma once

#include "Ghurund.h"
#include "core/Timer.h"
#include "Mouse.h"
#include "collection/List.h"
#include "Keyboard.h"
#include "Windowsx.h"
#include "EventConsumer.h"
#include "WindowProc.h"

namespace Ghurund {
    class Input {
    private:
        List<SystemMessage> messages;
        XMINT2 mousePos;
        bool keys[256];

        bool dispatchEvent(SystemMessage &message, EventDispatcher &consumer) {
            if(message.code == WM_KEYDOWN) {
                keys[message.wParam] = true;
                return consumer.dispatchKeyEvent(KeyEvent(KeyAction::DOWN, (int)message.wParam, message.time));
            } else if(message.code == WM_KEYUP) {
                keys[message.wParam] = false;
                return consumer.dispatchKeyEvent(KeyEvent(KeyAction::UP, (int)message.wParam, message.time));
            } else if(message.code == WM_LBUTTONDOWN) {
                return consumer.dispatchMouseButtonEvent(MouseButtonEvent(MouseAction::DOWN, MouseButton::LEFT, message.time));
            } else if(message.code == WM_LBUTTONUP) {
                return consumer.dispatchMouseButtonEvent(MouseButtonEvent(MouseAction::UP, MouseButton::LEFT, message.time));
            } else if(message.code == WM_MBUTTONDOWN) {
                return consumer.dispatchMouseButtonEvent(MouseButtonEvent(MouseAction::DOWN, MouseButton::MIDDLE, message.time));
            } else if(message.code == WM_MBUTTONUP) {
                return consumer.dispatchMouseButtonEvent(MouseButtonEvent(MouseAction::UP, MouseButton::MIDDLE, message.time));
            } else if(message.code == WM_RBUTTONDOWN) {
                return consumer.dispatchMouseButtonEvent(MouseButtonEvent(MouseAction::DOWN, MouseButton::RIGHT, message.time));
            } else if(message.code == WM_RBUTTONUP) {
                return consumer.dispatchMouseButtonEvent(MouseButtonEvent(MouseAction::UP, MouseButton::RIGHT, message.time));
            } else if(message.code == WM_MOUSEMOVE) {
                int x2 = GET_X_LPARAM(message.lParam);
                int y2 = GET_Y_LPARAM(message.lParam);
                bool result = consumer.dispatchMouseMotionEvent(MouseMotionEvent(XMINT2(x2-mousePos.x, y2-mousePos.y), message.time));
                mousePos.x = x2;
                mousePos.y = y2;
                return result;
            } else if(message.code == WM_MOUSEWHEEL) {
                return consumer.dispatchMouseWheelEvent(MouseWheelEvent(MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(message.wParam), message.time));
            } else if(message.code == WM_MOUSEHWHEEL) {
                return consumer.dispatchMouseWheelEvent(MouseWheelEvent(MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(message.wParam), message.time));
            }
            return false;	// shouldn't ever happen
        }

    public:
        void dispatchMessage(SystemMessage &message) {
            messages.add(message);
        }

        void dispatchEvents(EventDispatcher &consumer) {
            for(size_t i = 0; i < messages.Size;) {
                if(dispatchEvent(messages[i], consumer)) {
                    messages.removeAtKeepOrder(i);
                } else {
                    i++;
                }
            }
        }

        void clearEvents() {
            messages.clear();
        }

        XMINT2 getMousePos() const {
            return mousePos;
        }

        __declspec(property(get = getMousePos)) XMINT2 MousePos;

        const bool *getKeys() const {
            return keys;
        }

        __declspec(property(get = getKeys)) bool *Keys;
    };
}