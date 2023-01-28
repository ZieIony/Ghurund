#pragma once

#include "control/ControlContainer.h"
#include "core/window/Window.h"
#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
    class WindowWidthConstraint:public Constraint {
    private:
        Window& window;

    public:
        WindowWidthConstraint(Window& window):window(window) {}

        virtual void evaluate() override {
            value = (float)window.Size.Width;
        }
    };

    class WindowHeightConstraint:public Constraint {
    private:
        Window& window;

    public:
        WindowHeightConstraint(Window& window):window(window) {}

        virtual void evaluate() override {
            value = (float)window.Size.Height;
        }
    };

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

        void onMeasure(float parentWidth, float parentHeight) {
            __super::onMeasure(parentWidth, parentHeight);

            ConstraintGraph graph;
            Child->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();
        }

        virtual void repaint() {
            context->Window.refresh();
        }

        virtual void invalidate();

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;
    };
}