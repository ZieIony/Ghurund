#include "ghuipch.h"
#include "RootView.h"

#include "core/window/Cursor.h"
#include "ui/constraint/WindowConstraint.h"

namespace Ghurund::UI {
	bool RootView::onKeyEvent(const KeyEventArgs& event) {
		if (Focus && findFocus()->dispatchKeyEvent(event))
			return true;

		if (event.Action != Ghurund::Core::KeyAction::PRESSED)
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
					MouseButtonAction::RELEASED,
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

	RootView::RootView(UIContext& context):context(context) {
		Cursor = &Cursor::ARROW;
		Name = "root";
	}

	void RootView::requestLayout() {
		needsLayout = true;
	}

	PartialConstraintSet RootView::makeDefaultConstraints() const {
		return ConstraintSetInitializer{
			.width = makeIntrusive<WindowWidthConstraint>(context.Window),
			.height = makeIntrusive<WindowHeightConstraint>(context.Window)
		};
	}

};
