#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class WrapConstraint:public Constraint {
    public:
        WrapConstraint():Constraint(0.0f, true) {}

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            constraints.add(this);
        }

        virtual void evaluate() override;
    };
}