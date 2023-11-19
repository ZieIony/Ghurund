#pragma once

#include "core/window/Window.h"
#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
    class WindowWidthConstraint:public Constraint {
    private:
        Window& window;

    protected:
        WindowWidthConstraint(const WindowWidthConstraint& other):Constraint(other), window(other.window) {}

        virtual bool equalsImpl(const Object& other) const override;

    public:
        WindowWidthConstraint(Window& window):window(window) {}

        virtual void evaluate() override {
            value = (float)window.Size.Width;
        }

        virtual Object* clone() const {
            return ghnew WindowWidthConstraint(*this);
        }
    };

    class WindowHeightConstraint:public Constraint {
    private:
        Window& window;

    protected:
        WindowHeightConstraint(const WindowHeightConstraint& other):Constraint(other), window(other.window) {}

        virtual bool equalsImpl(const Object& other) const override;

    public:
        WindowHeightConstraint(Window& window):window(window) {}

        virtual void evaluate() override {
            value = (float)window.Size.Height;
        }

        virtual Object* clone() const {
            return ghnew WindowHeightConstraint(*this);
        }
    };
}