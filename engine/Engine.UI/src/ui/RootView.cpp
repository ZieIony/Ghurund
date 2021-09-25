#include "ghuipch.h"
#include "RootView.h"

#include "ui/Cursor.h"

namespace Ghurund::UI {
    RootView::RootView(UIContext& context) {
        this->context = &context;
        Cursor = &Cursor::ARROW;
    }

    void RootView::invalidate() {
        needsLayout = true;
    }

    bool RootView::dispatchKeyEvent(const KeyEventArgs& event) {
        if (__super::dispatchKeyEvent(event))
            return true;

        if (event.Action != Ghurund::Core::KeyAction::DOWN)
            return false;

        if (event.Key == VK_TAB) {
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
        } else if (event.Key == VK_ESCAPE) {
            if (Focus)
                findFocus()->clearFocus();
            if (capturedChild) {
                capturedChild->dispatchMouseButtonEvent(MouseButtonEventArgs({ -1,-1 }, MouseAction::UP, MouseButton::VIRTUAL, event.TimeMs, false));
                capturedChild->release();
                capturedChild = nullptr;
            }
            return true;
        } else if (event.Key == VK_UP) {
            focusUp();
        } else if (event.Key == VK_DOWN) {
            focusDown();
        } else if (event.Key == VK_LEFT) {
            focusLeft();
        } else if (event.Key == VK_RIGHT) {
            focusRight();
        }

        return false;
    }

    bool RootView::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (capturedChild) {
            auto position = capturedChild->PositionInWindow;
            bool inside = event.Position.x >= position.x && event.Position.x < position.x + capturedChild->Size.width &&
                event.Position.y >= position.y && event.Position.y < position.y + capturedChild->Size.height;
            auto result = capturedChild->dispatchMouseButtonEvent(event.translate(-position.x, -position.y, inside));
            return result;
        }

        return __super::dispatchMouseButtonEvent(event);
    }

    bool RootView::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (capturedChild) {
            auto position = capturedChild->PositionInWindow;
            bool inside = event.Position.x >= position.x && event.Position.x < position.x + capturedChild->Size.width &&
                event.Position.y >= position.y && event.Position.y < position.y + capturedChild->Size.height;
            return capturedChild->dispatchMouseMotionEvent(event.translate(-position.x, -position.y, inside));
        }

        return __super::dispatchMouseMotionEvent(event);
    }
};
