#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    class ParentLeftConstraint:public ValueConstraint {
    public:
        ParentLeftConstraint():ValueConstraint(0.0f) {}
    };

    class ParentRightConstraint:public Constraint {
    public:
        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Width);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

    class ParentTopConstraint:public ValueConstraint {
    public:
        ParentTopConstraint():ValueConstraint(0.0f) {}
    };

    class ParentBottomConstraint:public Constraint {
    public:
        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Height);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

    class ParentWidthConstraint:public Constraint {
    public:
        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Width);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

    class ParentHeightConstraint:public Constraint {
    public:
        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->Height);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };
}