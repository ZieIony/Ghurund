#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class RatioConstraint:public Constraint {
    public:
        float ratio = 1.0f;
        Constraint* constraint = nullptr;

        RatioConstraint() {}
        RatioConstraint(Constraint* constraint, float ratio):constraint(constraint), ratio(ratio) {}

        virtual void evaluate() override;

        virtual bool isConstant() const;
    };
}