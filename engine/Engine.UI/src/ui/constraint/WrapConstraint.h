#pragma once

#include "Constraint.h"
#include "core/SharedPointer.h"

namespace Ghurund::UI {

    class WrapWidthConstraint:public MinMaxConstraint {
    private:
        Control* control;

    public:
        WrapWidthConstraint():MinMaxConstraint(0.0f, false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;
    };

    class WrapHeightConstraint:public MinMaxConstraint {
    private:
        Control* control;

    public:
        WrapHeightConstraint():MinMaxConstraint(0.0f, false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;
    };
}