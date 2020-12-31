#include "RootView.h"

namespace Ghurund::UI {
    RootView::RootView(UIContext& context, Canvas& canvas) {
        this->canvas = &canvas;
        this->context = &context;
        this->context->Window.OnFocusedChanged.add([this](Ghurund::Window& window) {
            if (!window.Visible || Focused) {
                if (prevFocusedChild) {
                    prevFocusedChild->requestFocus();
                    prevFocusedChild->release();
                    prevFocusedChild = nullptr;
                }
            } else {
                setPointer(prevFocusedChild, Focus);
                clearFocus();
            }
            return true;
        });
    }

    void RootView::invalidate() {
        needsLayout = true;
    }

    bool RootView::dispatchKeyEvent(const KeyEventArgs& event) {
        if (__super::dispatchKeyEvent(event))
            return true;

        if (event.Action != KeyAction::DOWN)
            return false;

        if (event.Key == VK_TAB) {
            if (GetKeyState(VK_SHIFT) & 0x8000) {
                if (!focusPrevious() && Focus) {
                    clearFocus();
                    focusPrevious();
                }
            } else {
                if (!focusNext() && Focus) {
                    clearFocus();
                    focusNext();
                }
            }
            return true;
        } else if (event.Key == VK_ESCAPE) {
            clearFocus();
            if (capturedChild) {
                capturedChild->dispatchMouseButtonEvent(MouseButtonEventArgs({ -1,-1 }, MouseAction::UP, MouseButton::VIRTUAL, event.Time, false));
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
            return capturedChild->dispatchMouseButtonEvent(event.translate(-position.x, -position.y, inside));
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

        if (!__super::dispatchMouseMotionEvent(event))
            Cursor::ARROW.set();
        return true;
    }
};
