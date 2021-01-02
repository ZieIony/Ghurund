#include "Input.h"
#include "application/SystemWindow.h"

namespace Ghurund::Input {
    void Input::dispatchEvents(uint64_t time, Ghurund::SystemWindow& window) {
        while (!events.Empty) {
            WindowMessage wm = events[0];
            if (wm.time > time)
                return;
            events.removeAt(0);
            UINT msg = wm.code;
            WPARAM wParam = wm.wParam;
            int64_t time = wm.time;
            POINT p = wm.mousePos;

            if (msg == WM_KEYDOWN) {
                keys[(int)wParam] = true;
                window.dispatchKeyEvent(KeyEventArgs(KeyAction::DOWN, (int)wParam, time));
            } else if (msg == WM_KEYUP) {
                keys[(int)wParam] = false;
                window.dispatchKeyEvent(KeyEventArgs(KeyAction::UP, (int)wParam, time));
            } else if (msg == WM_CHAR) {
                window.dispatchKeyEvent(KeyEventArgs(KeyAction::CHAR, (int)wParam, time));
            } else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
                if (msg == WM_LBUTTONDOWN) {
                    window.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::DOWN, MouseButton::LEFT, time, true));
                } else if (msg == WM_LBUTTONUP) {
                    window.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::UP, MouseButton::LEFT, time, true));
                } else if (msg == WM_MBUTTONDOWN) {
                    window.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::DOWN, MouseButton::MIDDLE, time, true));
                } else if (msg == WM_MBUTTONUP) {
                    window.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::UP, MouseButton::MIDDLE, time, true));
                } else if (msg == WM_RBUTTONDOWN) {
                    window.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::DOWN, MouseButton::RIGHT, time, true));
                } else if (msg == WM_RBUTTONUP) {
                    window.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::UP, MouseButton::RIGHT, time, true));
                } else if (msg == WM_MOUSEMOVE) {
                    window.dispatchMouseMotionEvent(MouseMotionEventArgs({ p.x, p.y }, { p.x - prevMousePos.x, p.y - prevMousePos.y }, time, true));
                    prevMousePos = p;
                } else if (msg == WM_MOUSEWHEEL) {
                    window.dispatchMouseWheelEvent(MouseWheelEventArgs({ p.x, p.y }, MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wParam), time, true));
                } else if (msg == WM_MOUSEHWHEEL) {
                    window.dispatchMouseWheelEvent(MouseWheelEventArgs({ p.x, p.y }, MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(wParam), time, true));
                }
            }
        }
    }
}