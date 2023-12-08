#pragma once

#include "core/window/Window.h"
#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
    class WindowWidthConstraint:public Constraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

    private:
        Window& window;

    protected:
        WindowWidthConstraint(const WindowWidthConstraint& other):Constraint(other), window(other.window) {}

        virtual bool equalsImpl(const Object& other) const override;

    public:
        WindowWidthConstraint(Window& window):window(window) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override {
            evaluated = false;
        }

        virtual void evaluate() override {
            value = (float)window.Size.Width;
            evaluated = true;
        }

        virtual Object* clone() const {
            return ghnew WindowWidthConstraint(*this);
        }
    };

    class WindowHeightConstraint:public Constraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

    private:
        Window& window;

    protected:
        WindowHeightConstraint(const WindowHeightConstraint& other):Constraint(other), window(other.window) {}

        virtual bool equalsImpl(const Object& other) const override;

    public:
        WindowHeightConstraint(Window& window):window(window) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override {
            evaluated = false;
        }

        virtual void evaluate() override {
            value = (float)window.Size.Height;
            evaluated = true;
        }

        virtual Object* clone() const {
            return ghnew WindowHeightConstraint(*this);
        }
    };
}