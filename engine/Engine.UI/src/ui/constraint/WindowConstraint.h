#pragma once

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
}