#include "ghcpch.h"
#include "Input.h"
#include "gamepad/GamepadButtonEventArgs.h"

namespace Ghurund::Core {
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
                uint8_t c = MapVirtualKey(wParam, MAPVK_VK_TO_CHAR);
                keys[c] = true;
                consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::PRESSED, c, time));
            } else if (msg == WM_KEYUP) {
                uint8_t c = MapVirtualKey(wParam, MAPVK_VK_TO_CHAR);
                keys[c] = false;
                consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::RELEASED, c, time));
            } else if (msg == WM_CHAR) {
                consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::CHAR, (uint8_t)wParam, time));
            } else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
                if (msg == WM_LBUTTONDOWN) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::PRESSED, MouseButton::LEFT, time, true));
                } else if (msg == WM_LBUTTONUP) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::RELEASED, MouseButton::LEFT, time, true));
                } else if (msg == WM_MBUTTONDOWN) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::PRESSED, MouseButton::MIDDLE, time, true));
                } else if (msg == WM_MBUTTONUP) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::RELEASED, MouseButton::MIDDLE, time, true));
                } else if (msg == WM_RBUTTONDOWN) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::PRESSED, MouseButton::RIGHT, time, true));
                } else if (msg == WM_RBUTTONUP) {
                    consumer.dispatchMouseButtonEvent(MouseButtonEventArgs({ p.x, p.y }, MouseAction::RELEASED, MouseButton::RIGHT, time, true));
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

        for (auto key : keys) {
            if (key)
                consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::DOWN, key, time));
        }

		for (uint8_t i = 0; i < gamepadInput.getMaxGamepads(); i++) {
            auto state = gamepadInput.getState(i);
            if (state) {
                for (size_t j = 0; j < gamepadButtons.Size;j++) {
                    auto& button = GamepadButton::VALUES[j];
                    bool down = state->isButtonDown(button);
                    if (down && !gamepadButtons[j]) {
                        consumer.dispatchGamepadButtonEvent(GamepadButtonEventArgs(i, GamepadButtonAction::PRESSED, button, time));
                        gamepadButtons[j] = true;
                    }
                    if (!down && gamepadButtons[j]) {
                        consumer.dispatchGamepadButtonEvent(GamepadButtonEventArgs(i, GamepadButtonAction::RELEASED, button, time));
                        gamepadButtons[j] = false;
                    }
                    if (down && gamepadButtons[j])
                        consumer.dispatchGamepadButtonEvent(GamepadButtonEventArgs(i, GamepadButtonAction::DOWN, button, time));
                }
                consumer.dispatchGamepadStickEvent(GamepadStickEventArgs(i, GamepadStick::LEFT, state->LeftStick, time));
                consumer.dispatchGamepadStickEvent(GamepadStickEventArgs(i, GamepadStick::RIGHT, state->RightStick, time));
                consumer.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(i, GamepadTrigger::LEFT, state->LeftTrigger, time));
                consumer.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(i, GamepadTrigger::RIGHT, state->RightTrigger, time));
                delete state;
            }
        }
    }
}