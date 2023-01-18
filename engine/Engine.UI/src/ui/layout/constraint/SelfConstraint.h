#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    class SelfWidthConstraint:public Constraint {
    private:
        float ratio, offset;

    public:
        SelfWidthConstraint(float ratio = 1.0f, float offset = 0.0f):ratio(ratio), offset(offset) {}

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Width);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value * ratio + offset;
        }
    };

    class SelfHeightConstraint:public Constraint {
    private:
        float ratio, offset;

    public:
        SelfHeightConstraint(float ratio = 1.0f, float offset = 0.0f):ratio(ratio), offset(offset) {}

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Height);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value * ratio + offset;
        }
    };
}