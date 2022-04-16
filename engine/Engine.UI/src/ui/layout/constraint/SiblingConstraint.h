#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    class SiblingLeftConstraint:public Constraint {
    private:
        const AString name;

    public:
        SiblingLeftConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Left);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

    class SiblingRightConstraint:public Constraint {
    private:
        const AString name;

    public:
        SiblingRightConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Right);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

    class SiblingTopConstraint:public Constraint {
    private:
        const AString name;

    public:
        SiblingTopConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Top);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

    class SiblingBottomConstraint:public Constraint {
    private:
        const AString name;

    public:
        SiblingBottomConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Bottom);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

    class SiblingWidthConstraint:public Constraint {
    private:
        const AString name;

    public:
        SiblingWidthConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Width);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

    class SiblingHeightConstraint:public Constraint {
    private:
        const AString name;

    public:
        SiblingHeightConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Height);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value;
        }
    };

}