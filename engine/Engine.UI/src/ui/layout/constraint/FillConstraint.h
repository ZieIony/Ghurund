#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class WidthFillConstraint:public Constraint {
    public:
        virtual void resolve(Control& control) override;

        virtual void evaluate() override;
    };

    class HeightFillConstraint:public Constraint {
    public:
        virtual void resolve(Control& control) override;

        virtual void evaluate() override;
    };
}