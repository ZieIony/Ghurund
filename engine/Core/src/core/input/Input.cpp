#include "ghcpch.h"
#include "Input.h"
#include "gamepad/GamepadButtonEventArgs.h"

#include <Windows.h>
#include <xinput.h>
#include <windowsx.h>

namespace Ghurund::Core {
	void Input::dispatchWindowEvents(uint64_t time, NotNull<EventConsumer> consumer) {
		while (!events.Empty) {
			WindowMessage wm = events[0];
			if (wm.time > time)
				break;
			events.removeAt(0);
			UINT msg = wm.code;
			int64_t time = wm.time;

			if (msg >= WM_KEYFIRST && msg <= WM_KEYLAST) {
				if (msg == WM_KEYDOWN) {
					uint8_t c = MapVirtualKey(wm.wParam, MAPVK_VK_TO_CHAR);
					keys[c].isDown = true;
					keys[c].pressedTime = time;
					consumer->dispatchKeyEvent(KeyEventArgs(KeyAction::PRESSED, c, 0, time));
				} else if (msg == WM_KEYUP) {
					uint8_t c = MapVirtualKey(wm.wParam, MAPVK_VK_TO_CHAR);
					keys[c].isDown = false;
					consumer->dispatchKeyEvent(KeyEventArgs(KeyAction::RELEASED, c, 0, time));
				} else if (msg == WM_CHAR) {
					consumer->dispatchKeyEvent(KeyEventArgs(KeyAction::CHAR, (uint8_t)wm.wParam, 0, time));
				}
			} else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
				IntPoint p = { GET_X_LPARAM(wm.lParam), GET_Y_LPARAM(wm.lParam) };
				if (msg == WM_LBUTTONDOWN) {
					mouseButtonLeft.isDown = true;
					mouseButtonLeft.pressedTime = time;
					consumer->dispatchMouseButtonEvent(MouseButtonEventArgs(p, MouseAction::PRESSED, MouseButton::LEFT, 0, time, true));
				} else if (msg == WM_LBUTTONUP) {
					mouseButtonLeft.isDown = false;
					auto event = MouseButtonEventArgs(
						p,
						MouseAction::RELEASED,
						MouseButton::LEFT,
						time - mouseButtonLeft.pressedTime,
						time,
						true
					);
					consumer->dispatchMouseButtonEvent(event);
				} else if (msg == WM_MBUTTONDOWN) {
					mouseButtonMiddle.isDown = true;
					mouseButtonMiddle.pressedTime = time;
					consumer->dispatchMouseButtonEvent(MouseButtonEventArgs(p, MouseAction::PRESSED, MouseButton::MIDDLE, 0, time, true));
				} else if (msg == WM_MBUTTONUP) {
					mouseButtonMiddle.isDown = false;
					auto event = MouseButtonEventArgs(
						p,
						MouseAction::RELEASED,
						MouseButton::MIDDLE,
						time - mouseButtonMiddle.pressedTime,
						time,
						true
					);
					consumer->dispatchMouseButtonEvent(event);
				} else if (msg == WM_RBUTTONDOWN) {
					mouseButtonRight.isDown = true;
					mouseButtonRight.pressedTime = time;
					consumer->dispatchMouseButtonEvent(MouseButtonEventArgs(p, MouseAction::PRESSED, MouseButton::RIGHT, 0, time, true));
				} else if (msg == WM_RBUTTONUP) {
					mouseButtonRight.isDown = false;
					auto event = MouseButtonEventArgs(
						p,
						MouseAction::RELEASED,
						MouseButton::RIGHT,
						time - mouseButtonRight.pressedTime,
						time,
						true
					);
					consumer->dispatchMouseButtonEvent(event);
				} else if (msg == WM_MOUSEMOVE) {
					consumer->dispatchMouseMotionEvent(MouseMotionEventArgs(p, p - prevMousePos, time, true));
					prevMousePos = p;
				} else if (msg == WM_MOUSEWHEEL) {
					consumer->dispatchMouseWheelEvent(MouseWheelEventArgs(p, MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wm.wParam), time, true));
				} else if (msg == WM_MOUSEHWHEEL) {
					consumer->dispatchMouseWheelEvent(MouseWheelEventArgs(p, MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(wm.wParam), time, true));
				}
			}
		}
	}

	void Input::dispatchMouseButtonDownEvents(uint64_t time, NotNull<EventConsumer> consumer) {
		if (mouseButtonLeft.isDown) {
			auto event = MouseButtonEventArgs(
				prevMousePos,
				MouseAction::DOWN,
				MouseButton::LEFT,
				time - mouseButtonLeft.pressedTime,
				time,
				true
			);
			consumer->dispatchMouseButtonEvent(event);
		}
		if (mouseButtonMiddle.isDown) {
			auto event = MouseButtonEventArgs(
				prevMousePos,
				MouseAction::DOWN,
				MouseButton::MIDDLE,
				time - mouseButtonMiddle.pressedTime,
				time,
				true
			);
			consumer->dispatchMouseButtonEvent(event);
		}
		if (mouseButtonRight.isDown) {
			auto event = MouseButtonEventArgs(
				prevMousePos,
				MouseAction::DOWN,
				MouseButton::RIGHT,
				time - mouseButtonRight.pressedTime,
				time,
				true
			);
			consumer->dispatchMouseButtonEvent(event);
		}
	}

	void Input::dispatchKeyDownEvents(uint64_t time, NotNull<EventConsumer> consumer) {
		for (size_t i = 0; i < keys.Size; i++) {
			if (keys[i].isDown)
				consumer->dispatchKeyEvent(KeyEventArgs(KeyAction::DOWN, i, keys[i].pressedTime, time));
		}
	}

	void Input::dispatchGamepadEvents(uint64_t time, NotNull<EventConsumer> consumer) {
		for (uint8_t gamepadIndex = 0; gamepadIndex < getMaxGamepads(); gamepadIndex++) {
			auto state = getGamepadState(gamepadIndex);
			if (state) {
				for (size_t j = 0; j < gamepadButtonState.Size; j++) {
					auto& gamepadButton = GamepadButton::VALUES[j];
					auto& buttonState = gamepadButtonState[j];
					bool down = state->isButtonDown(gamepadButton);
					if (down && !buttonState.isDown) {
						auto event = GamepadButtonEventArgs(
							gamepadIndex,
							GamepadButtonAction::PRESSED,
							gamepadButton,
							0,
							time
						);
						consumer->dispatchGamepadButtonEvent(event);
						buttonState.isDown = true;
						buttonState.pressedTime = time;
					}
					if (!down && buttonState.isDown) {
						auto event = GamepadButtonEventArgs(
							gamepadIndex,
							GamepadButtonAction::RELEASED,
							gamepadButton,
							time - buttonState.pressedTime,
							time
						);
						consumer->dispatchGamepadButtonEvent(event);
						buttonState.isDown = false;
					}
					if (down && buttonState.isDown) {
						auto event = GamepadButtonEventArgs(
							gamepadIndex,
							GamepadButtonAction::DOWN,
							gamepadButton,
							time - buttonState.pressedTime,
							time
						);
						consumer->dispatchGamepadButtonEvent(event);
					}
				}
				consumer->dispatchGamepadStickEvent(GamepadStickEventArgs(gamepadIndex, GamepadStick::LEFT, state->LeftStick, time));
				consumer->dispatchGamepadStickEvent(GamepadStickEventArgs(gamepadIndex, GamepadStick::RIGHT, state->RightStick, time));
				consumer->dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(gamepadIndex, GamepadTrigger::LEFT, state->LeftTrigger, time));
				consumer->dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(gamepadIndex, GamepadTrigger::RIGHT, state->RightTrigger, time));
				delete state;
			}
		}
	}

	uint8_t Input::getMaxGamepads() const {
		return XUSER_MAX_COUNT;
	}

	GamepadState* Input::getGamepadState(uint8_t index) {
		DWORD dwResult;
		XINPUT_STATE state = {};

		dwResult = XInputGetState(index, &state);

		if (dwResult == ERROR_SUCCESS) {
			auto gamepad = state.Gamepad;
			return ghnew GamepadState(
				(uint16_t)gamepad.wButtons,
				FloatPoint{ shortToFloat(gamepad.sThumbLX), shortToFloat(gamepad.sThumbLY) },
				FloatPoint{ shortToFloat(gamepad.sThumbRX), shortToFloat(gamepad.sThumbRY) },
				gamepad.bLeftTrigger / 255.0f,
				gamepad.bRightTrigger / 255.0f
			);
		} else {
			return nullptr;
		}
	}
}