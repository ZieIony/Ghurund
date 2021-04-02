#include "ghcpch.h"
#include "Input.h"

namespace Ghurund {
    void Input::dispatchEvents(uint64_t time, EventConsumer& consumer) {
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
                consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::DOWN, (int)wParam, time));
            } else if (msg == WM_KEYUP) {
                keys[(int)wParam] = false;
                consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::UP, (int)wParam, time));
            } else if (msg == WM_CHAR) {
                consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::CHAR, (int)wParam, time));
            } else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
                if (msg == WM_LBUTTONDOWN) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::DOWN, MouseButton::LEFT, time, true));
                } else if (msg == WM_LBUTTONUP) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::UP, MouseButton::LEFT, time, true));
                } else if (msg == WM_MBUTTONDOWN) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::DOWN, MouseButton::MIDDLE, time, true));
                } else if (msg == WM_MBUTTONUP) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::UP, MouseButton::MIDDLE, time, true));
                } else if (msg == WM_RBUTTONDOWN) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::DOWN, MouseButton::RIGHT, time, true));
                } else if (msg == WM_RBUTTONUP) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::UP, MouseButton::RIGHT, time, true));
                } else if (msg == WM_MOUSEMOVE) {
                    consumer.dispatchMouseMotionEvent(MouseMotionEventArgs({ p.x, p.y }, { p.x - prevMousePos.x, p.y - prevMousePos.y }, time, true));
                    prevMousePos = p;
                } else if (msg == WM_MOUSEWHEEL) {
                    consumer.dispatchMouseWheelEvent(MouseWheelEventArgs({ p.x, p.y }, MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wParam), time, true));
                } else if (msg == WM_MOUSEHWHEEL) {
                    consumer.dispatchMouseWheelEvent(MouseWheelEventArgs({ p.x, p.y }, MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(wParam), time, true));
                }
            }
        }
    }
}