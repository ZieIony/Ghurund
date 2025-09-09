#include "ghuipch.h"
#include "RootView.h"

#include "core/window/Cursor.h"
#include "ui/constraint/WindowConstraint.h"

namespace Ghurund::UI {
	RootView::RootView(IUIContext& context) {
		this->context = &context;
		Cursor = &Cursor::ARROW;
		Name = "root";
	}

	void RootView::requestLayout() {
		needsLayout = true;
	}

	bool RootView::dispatchKeyEvent(const KeyEventArgs& event) {
		if (Focus && findFocus()->dispatchKeyEvent(event))
			return true;

		if (event.Action != Ghurund::Core::KeyAction::DOWN)
			return false;

		if (event.KeyCode == VK_TAB) {
			if (GetKeyState(VK_SHIFT) & 0x8000) {
				if (!focusPrevious() && Focus) {
					findFocus()->clearFocus();
					focusPrevious();
				}
			} else {
				if (!focusNext() && Focus) {
					findFocus()->clearFocus();
					focusNext();
				}
			}
			return true;
		} else if (event.KeyCode == VK_ESCAPE) {
			if (Focus)
				findFocus()->clearFocus();
			if (capturedChild) {
				auto mouseButtonEvent = MouseButtonEventArgs(
					{ -1,-1 },
					MouseAction::RELEASED,
					MouseButton::VIRTUAL,
					0,
					event.TimeMs,
					false
				);
				capturedChild->dispatchMouseButtonEvent(mouseButtonEvent);
				capturedChild->release();
				capturedChild = nullptr;
			}
			return true;
		} else if (event.KeyCode == VK_UP) {
			focusUp();
		} else if (event.KeyCode == VK_DOWN) {
			focusDown();
		} else if (event.KeyCode == VK_LEFT) {
			focusLeft();
		} else if (event.KeyCode == VK_RIGHT) {
			focusRight();
		}

		return false;
	}

	bool RootView::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
		if (capturedChild) {
			auto position = capturedChild->PositionInWindow;
			bool inside = event.Position.x >= position.x && event.Position.x < position.x + capturedChild->Size.Width &&
				event.Position.y >= position.y && event.Position.y < position.y + capturedChild->Size.Height;
			auto result = capturedChild->dispatchMouseButtonEvent(event.translate(-position.x, -position.y, inside));
			return result;
		}

		return __super::dispatchMouseButtonEvent(event);
	}

	bool RootView::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
		if (capturedChild) {
			auto position = capturedChild->PositionInWindow;
			bool inside = event.Position.x >= position.x && event.Position.x < position.x + capturedChild->Size.Width &&
				event.Position.y >= position.y && event.Position.y < position.y + capturedChild->Size.Height;
			return capturedChild->dispatchMouseMotionEvent(event.translate(-position.x, -position.y, inside));
		}

		return __super::dispatchMouseMotionEvent(event);
	}

	PartialConstraintSet RootView::makeDefaultConstraints() const {
		return ConstraintSetInitializer{
			.width = makeIntrusive<WindowWidthConstraint>(context->Window),
			.height = makeIntrusive<WindowHeightConstraint>(context->Window)
		};
	}

};
