#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class FlowWidthConstraint:public MinMaxConstraint {
    public:
        FlowWidthConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;
    };

    class FlowHeightConstraint:public MinMaxConstraint {
    public:
        FlowHeightConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;
    };
}