#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    class SiblingLeftConstraint:public OffsetConstraint {
    private:
        const AString name;

    public:
        SiblingLeftConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Left);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingRightConstraint:public OffsetConstraint {
    private:
        const AString name;

    public:
        SiblingRightConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Right);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingTopConstraint:public OffsetConstraint {
    private:
        const AString name;
        float offset;

    public:
        SiblingTopConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Top);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingBottomConstraint:public OffsetConstraint {
    private:
        const AString name;

    public:
        SiblingBottomConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Bottom);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingWidthConstraint:public MinMaxConstraint {
    private:
        const AString name;

    public:
        SiblingWidthConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Width);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }
    };

    class SiblingHeightConstraint:public MinMaxConstraint {
    private:
    const AString name;
    
    public:
        SiblingHeightConstraint(const AString& name): name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control, List<Constraint*>& constraints) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Height);
            constraints.add(this);
        }

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }
    };
}