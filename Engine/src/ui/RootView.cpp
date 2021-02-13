#include "RootView.h"

#include "ui/Cursor.h"

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
                Control* focus = Focus;
                if (focus) {
                    while (focus->Focus)
                        focus = focus->Focus;
                    setPointer(prevFocusedChild, focus);
                    clearFocus();
                }

            }
            return true;
        });
    }

    void RootView::invalidate() {
        needsLayout = true;
    }

    bool RootView::dispatchKeyEvent(const Ghurund::Input::KeyEventArgs& event) {
        if (__super::dispatchKeyEvent(event))
            return true;

        if (event.Action != Ghurund::Input::KeyAction::DOWN)
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
                capturedChild->dispatchMouseButtonEvent(Ghurund::Input::MouseButtonEventArgs({ -1,-1 }, Ghurund::Input::MouseAction::UP, Ghurund::Input::MouseButton::VIRTUAL, event.TimeMs, false));
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

    bool RootView::dispatchMouseButtonEvent(const Ghurund::Input::MouseButtonEventArgs& event) {
        if (capturedChild) {
            auto position = capturedChild->PositionInWindow;
            bool inside = event.Position.x >= position.x && event.Position.x < position.x + capturedChild->Size.width &&
                event.Position.y >= position.y && event.Position.y < position.y + capturedChild->Size.height;
            return capturedChild->dispatchMouseButtonEvent(event.translate(-position.x, -position.y, inside));
        }

        return __super::dispatchMouseButtonEvent(event);
    }

    bool RootView::dispatchMouseMotionEvent(const Ghurund::Input::MouseMotionEventArgs& event) {
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
