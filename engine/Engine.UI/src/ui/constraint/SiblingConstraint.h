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

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

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

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }
    };

    class SiblingTopConstraint:public OffsetConstraint {
    private:
        const AString name;

    public:
        SiblingTopConstraint(const AString& name):name(name) {}

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

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

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

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

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

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

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }
    };
}