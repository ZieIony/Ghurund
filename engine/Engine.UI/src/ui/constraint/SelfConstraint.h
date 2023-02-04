#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "core/math/MathUtils.h"

namespace Ghurund::UI {
    class Control;

    class SelfWidthConstraint:public MinMaxConstraint {
    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }
    };

    class SelfHeightConstraint:public MinMaxConstraint {
    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }
    };

    class LeftWidthConstraint:public Constraint {
    private:
        SharedPointer<Constraint> left, width;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = left->Value + width->Value;
        }
    };

    class CenterLeftConstraint:public Constraint {
    private:
        SharedPointer<Constraint> left, width, right;

    public:
        CenterLeftConstraint(const SharedPointer<Constraint> left, const SharedPointer<Constraint> width, const SharedPointer<Constraint> right)
            :left(left), width(width), right(right) {
                dependencies.addAll({ this->left, this->width, this->right });
        }

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (right->Value + left->Value - width->Value) / 2;
        }
    };

    class LeftRightConstraint:public Constraint {
    private:
        SharedPointer<Constraint> left, right;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = right->Value - left->Value;
        }
    };

    class CenterRightConstraint:public Constraint {
    private:
        SharedPointer<Constraint> left, width, right;

    public:
        CenterRightConstraint(const SharedPointer<Constraint> left, const SharedPointer<Constraint> width, const SharedPointer<Constraint> right)
            :left(left), width(width), right(right) {
            dependencies.addAll({ this->left, this->width, this->right });
        }

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (right->Value + left->Value + width->Value) / 2;
        }
    };

    class WidthRightConstraint:public Constraint {
    private:
        SharedPointer<Constraint> width, right;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = right->Value - width->Value;
        }
    };

    class TopHeightConstraint:public Constraint {
    private:
        SharedPointer<Constraint> top, height;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = top->Value + height->Value;
        }
    };

    class CenterTopConstraint:public Constraint {
    private:
        SharedPointer<Constraint> top, height, bottom;

    public:
        CenterTopConstraint(const SharedPointer<Constraint> top, const SharedPointer<Constraint> height, const SharedPointer<Constraint> bottom)
            :top(top), height(height), bottom(bottom) {
            dependencies.addAll({ this->top, this->height, this->bottom });
        }

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (bottom->Value + top->Value - height->Value) / 2;
        }
    };

    class TopBottomConstraint:public Constraint {
    private:
        SharedPointer<Constraint> top, bottom;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = bottom->Value - top->Value;
        }
    };

    class CenterBottomConstraint:public Constraint {
    private:
        SharedPointer<Constraint> top, height, bottom;

    public:
        CenterBottomConstraint(const SharedPointer<Constraint> top, const SharedPointer<Constraint> height, const SharedPointer<Constraint> bottom)
            :top(top), height(height), bottom(bottom) {
            dependencies.addAll({ this->top, this->height, this->bottom });
        }

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (bottom->Value + top->Value + height->Value) / 2;
        }
    };

    class HeightBottomConstraint:public Constraint {
    private:
        SharedPointer<Constraint> height, bottom;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = bottom->Value - height->Value;
        }
    };
}