#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class WrapConstraint:public Constraint {
    public:
        WrapConstraint():Constraint(0.0f, true) {}

        virtual void resolve(Control& control) override {}

        virtual void evaluate() override;
    };
}