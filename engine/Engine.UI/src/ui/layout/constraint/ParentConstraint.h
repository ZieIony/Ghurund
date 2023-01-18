#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
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

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Width);
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

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Height);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class ParentWidthConstraint:public Constraint {
    private:
        float ratio, offset;

    public:
        ParentWidthConstraint(float ratio = 1.0f, float offset = 0.0f):ratio(ratio), offset(offset) {}

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Width);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value * ratio + offset;
        }
    };

    class ParentHeightConstraint:public Constraint {
    private:
        float ratio, offset;

    public:
        ParentHeightConstraint(float ratio = 1.0f, float offset = 0.0f):ratio(ratio), offset(offset) {}

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Height);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value * ratio + offset;
        }
    };
}