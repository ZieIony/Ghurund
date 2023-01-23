#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "core/math/MathUtils.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    class ParentLeftConstraint:public ValueConstraint {
    public:
        ParentLeftConstraint(float offset = 0.0f):ValueConstraint(offset) {}
    };

    class ParentRightConstraint:public Constraint {
    private:
        float offset;

    public:
        ParentRightConstraint(float offset = 0.0f):offset(offset) {}

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Width);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class ParentTopConstraint:public ValueConstraint {
    public:
        ParentTopConstraint(float offset = 0.0f):ValueConstraint(offset) {}
    };

    class ParentBottomConstraint:public Constraint {
    private:
        float offset;

    public:
        ParentBottomConstraint(float offset = 0.0f):offset(offset) {}

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Height);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class ParentWidthConstraint:public MinMaxConstraint {
    public:
        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Width);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }
    };

    class ParentHeightConstraint:public MinMaxConstraint {
    public:
        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Height);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }
    };
}