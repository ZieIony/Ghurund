#pragma once

#include "control/ControlContainer.h"
#include "core/window/Window.h"

namespace Ghurund::UI {
    class RootView: public ControlContainer {
    private:
        Control* prevFocusedChild = nullptr;
        Control* capturedChild = nullptr;
        UIContext* context = nullptr;
        bool focused = false;

    public:
        RootView(UIContext& context);

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

        virtual void setCapturedChild(Control* control) override {
            this->capturedChild = control;
        }

        virtual UIContext* getContext() override {
            return context;
        }

        virtual void repaint() {
            context->Window.refresh();
        }

        virtual void invalidate();

        virtual bool dispatchKeyEvent(const Ghurund::KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const Ghurund::MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const Ghurund::MouseMotionEventArgs& event) override;
    };
}