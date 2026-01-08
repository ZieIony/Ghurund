#include "ghcpch.h"
#include "Input.h"

#include <Windows.h>
#include <windowsx.h>

namespace Ghurund::Core {
	void Input::dispatchWindowEvents(uint64_t time, EventConsumer& consumer) {
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
					consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::PRESSED, c, 0, time));
				} else if (msg == WM_KEYUP) {
					uint8_t c = MapVirtualKey(wm.wParam, MAPVK_VK_TO_CHAR);
					keys[c].isDown = false;
					consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::RELEASED, c, 0, time));
				} else if (msg == WM_CHAR) {
					consumer.dispatchKeyEvent(KeyEventArgs(KeyAction::CHAR, (uint8_t)wm.wParam, 0, time));
				}
			} else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
				XMINT2 p = { GET_X_LPARAM(wm.lParam), GET_Y_LPARAM(wm.lParam) };
				if (msg == WM_LBUTTONDOWN) {
					mouseButtonLeft.isDown = true;
					mouseButtonLeft.pressedTime = time;
					consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(p, MouseButtonAction::PRESSED, MouseButton::LEFT, 0, time, true));
				} else if (msg == WM_LBUTTONUP) {
					mouseButtonLeft.isDown = false;
					auto event = MouseButtonEventArgs(
						p,
						MouseButtonAction::RELEASED,
						MouseButton::LEFT,
						time - mouseButtonLeft.pressedTime,
						time,
						true
					);
					consumer.dispatchMouseButtonEvent(event);
				} else if (msg == WM_MBUTTONDOWN) {
					mouseButtonMiddle.isDown = true;
					mouseButtonMiddle.pressedTime = time;
					consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(p, MouseButtonAction::PRESSED, MouseButton::MIDDLE, 0, time, true));
				} else if (msg == WM_MBUTTONUP) {
					mouseButtonMiddle.isDown = false;
					auto event = MouseButtonEventArgs(
						p,
						MouseButtonAction::RELEASED,
						MouseButton::MIDDLE,
						time - mouseButtonMiddle.pressedTime,
						time,
						true
					);
					consumer.dispatchMouseButtonEvent(event);
				} else if (msg == WM_RBUTTONDOWN) {
					mouseButtonRight.isDown = true;
					mouseButtonRight.pressedTime = time;
					consumer.dispatchMouseButtonEvent(MouseButtonEventArgs(p, MouseButtonAction::PRESSED, MouseButton::RIGHT, 0, time, true));
				} else if (msg == WM_RBUTTONUP) {
					mouseButtonRight.isDown = false;
					auto event = MouseButtonEventArgs(
						p,
						MouseButtonAction::RELEASED,
						MouseButton::RIGHT,
						time - mouseButtonRight.pressedTime,
						time,
						true
					);
					consumer.dispatchMouseButtonEvent(event);
				} else if (msg == WM_MOUSEMOVE) {
					consumer.dispatchMouseMotionEvent(MouseMotionEventArgs(p, p - prevMousePos, time, true));
					prevMousePos = p;
				} else if (msg == WM_MOUSEWHEEL) {
					consumer.dispatchMouseWheelEvent(MouseWheelEventArgs(p, MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wm.wParam), time, true));
				} else if (msg == WM_MOUSEHWHEEL) {
					consumer.dispatchMouseWheelEvent(MouseWheelEventArgs(p, MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(wm.wParam), time, true));
				}
			}
		}
	}

	void Input::dispatchMouseButtonDownEvents(uint64_t time, EventConsumer& consumer) {
		if (mouseButtonLeft.isDown) {
			auto event = MouseButtonEventArgs(
				prevMousePos,
				MouseButtonAction::DOWN,
				MouseButton::LEFT,
				time - mouseButtonLeft.pressedTime,
				time,
				true
			);
			consumer.dispatchMouseButtonEvent(event);
		}
		if (mouseButtonMiddle.isDown) {
			auto event = MouseButtonEventArgs(
				prevMousePos,
				MouseButtonAction::DOWN,
				MouseButton::MIDDLE,
				time - mouseButtonMiddle.pressedTime,
				time,
				true
			);
			consumer.dispatchMouseButtonEvent(event);
		}
		if (mouseButtonRight.isDown) {
			auto event = MouseButtonEventArgs(
				prevMousePos,
				MouseButtonAction::DOWN,
				MouseButton::RIGHT,
				time - mouseButtonRight.pressedTime,
				time,
				true
			);
			consumer.dispatchMouseButtonEvent(event);
		}
	}

	void Input::dispatchKeyDownEvents(uint64_t time, EventConsumer& consumer) {
		EventConsumer* c = &consumer;
		for (size_t i = 0; i < keys.Size; i++) {
			if (keys[i].isDown)
				c->dispatchKeyEvent(KeyEventArgs(KeyAction::DOWN, i, keys[i].pressedTime, time));
		}
	}

	void Input::dispatchGamepadEvents(uint64_t time, EventConsumer& consumer) {
		gamepadInput.dispatchEvents(time, consumer);
	}
}