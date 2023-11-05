#pragma once

#include "control/ControlContainer.h"
#include "core/window/Window.h"
#include "ui/constraint/WindowConstraint.h"

namespace Ghurund::UI {
    class RootView: public ControlContainer {
    private:
        Control* prevFocusedChild = nullptr;
        IUIContext* context = nullptr;
        bool focused = false;

    public:
        RootView(IUIContext& context);

        ~RootView() {
            if (prevFocusedChild)
                prevFocusedChild->release();
        }

        virtual bool isFocused() const override {
            return focused;
        }

        inline void setFocused(bool focused) {
            if (this->focused == focused)
                return;
            this->focused = focused;
            if (focused) {
                if (prevFocusedChild) {
                    prevFocusedChild->requestFocus();
                    prevFocusedChild->release();
                    prevFocusedChild = nullptr;
                }
            } else {
                Control* focus = findFocus();
                if (focus) {
                    setPointer(prevFocusedChild, focus);
                    focus->clearFocus();
                }
            }
        }

        __declspec(property(get = isFocused, put = setFocused)) bool Focused;

        virtual IUIContext* getContext() override {
            return context;
        }

        virtual void repaint() {
            context->Window.refresh();
        }

        virtual void requestLayout();

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;
    };
}