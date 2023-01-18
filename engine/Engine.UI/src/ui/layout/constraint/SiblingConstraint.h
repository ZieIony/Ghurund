#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    class SiblingLeftConstraint:public Constraint {
    private:
        const AString name;
        float offset;

    public:
        SiblingLeftConstraint(const AString& name, float offset = 0.0f):name(name), offset(offset) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Left);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingRightConstraint:public Constraint {
    private:
        const AString name;
        float offset;

    public:
        SiblingRightConstraint(const AString& name, float offset = 0.0f):name(name), offset(offset) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Right);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingTopConstraint:public Constraint {
    private:
        const AString name;
        float offset;

    public:
        SiblingTopConstraint(const AString& name, float offset = 0.0f):name(name), offset(offset) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Top);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingBottomConstraint:public Constraint {
    private:
        const AString name;
        float offset;

    public:
        SiblingBottomConstraint(const AString& name, float offset = 0.0f):name(name), offset(offset) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Bottom);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingWidthConstraint:public Constraint {
    private:
        const AString name;
        float ratio, offset;

    public:
        SiblingWidthConstraint(const AString& name, float ratio = 1.0f, float offset = 0.0f)
            :name(name), ratio(ratio), offset(offset) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Width);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value * ratio + offset;
        }
    };

    class SiblingHeightConstraint:public Constraint {
    private:
        const AString name;
        float ratio, offset;

    public:
        SiblingHeightConstraint(const AString& name, float ratio = 1.0f, float offset = 0.0f)
            :name(name), ratio(ratio), offset(offset) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control) override {
            dependencies.clear();
            dependencies.add(&control.Parent->find(name, false)->Height);
        }

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value * ratio + offset;
        }
    };
}