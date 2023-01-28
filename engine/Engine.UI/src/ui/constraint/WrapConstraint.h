#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class WrapWidthConstraint:public MinMaxConstraint {
    public:
        WrapWidthConstraint():MinMaxConstraint(0.0f, false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;
    };

    class WrapHeightConstraint:public MinMaxConstraint {
    public:
        WrapHeightConstraint():MinMaxConstraint(0.0f, false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;
    };
}