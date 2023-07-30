#pragma once

#include "Constraint.h"
#include "core/SharedPointer.h"

namespace Ghurund::UI {

    class WrapWidthConstraint:public MinMaxConstraint {
    private:
        Control* control = nullptr;

    public:
        WrapWidthConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;
    };

    class WrapHeightConstraint:public MinMaxConstraint {
    private:
        Control* control = nullptr;

    public:
        WrapHeightConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;
    };
}