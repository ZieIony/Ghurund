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
        Constraint* left, * width;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = left->Value + width->Value;
        }
    };

    class CenterLeftConstraint:public Constraint {
    private:
        std::shared_ptr<Constraint> left, width, right;

    public:
        CenterLeftConstraint(std::shared_ptr<Constraint> left, std::shared_ptr<Constraint> width, std::shared_ptr<Constraint> right)
            :left(left), width(width), right(right) {
            dependencies.addAll({ this->left.get(), this->width.get(), this->right.get() });
        }

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (right->Value + left->Value - width->Value) / 2;
        }
    };

    class LeftRightConstraint:public Constraint {
    private:
        Constraint* left, * right;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = right->Value - left->Value;
        }
    };

    class CenterRightConstraint:public Constraint {
    private:
        std::shared_ptr<Constraint> left, width, right;

    public:
        CenterRightConstraint(std::shared_ptr<Constraint> left, std::shared_ptr<Constraint> width, std::shared_ptr<Constraint> right)
            :left(left), width(width), right(right) {
            dependencies.addAll({ this->left.get(), this->width.get(), this->right.get() });
        }

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (right->Value + left->Value + width->Value) / 2;
        }
    };

    class WidthRightConstraint:public Constraint {
    private:
        Constraint* width, * right;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = right->Value - width->Value;
        }
    };

    class TopHeightConstraint:public Constraint {
    private:
        Constraint* top, * height;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = top->Value + height->Value;
        }
    };

    class CenterTopConstraint:public Constraint {
    private:
        std::shared_ptr<Constraint> top, height, bottom;

    public:
        CenterTopConstraint(std::shared_ptr<Constraint> top, std::shared_ptr<Constraint> height, std::shared_ptr<Constraint> bottom)
            :top(top), height(height), bottom(bottom) {
            dependencies.addAll({ this->top.get(), this->height.get(), this->bottom.get() });
        }

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (bottom->Value + top->Value - height->Value) / 2;
        }
    };

    class TopBottomConstraint:public Constraint {
    private:
        Constraint* top, * bottom;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = bottom->Value - top->Value;
        }
    };

    class CenterBottomConstraint:public Constraint {
    private:
        std::shared_ptr<Constraint> top, height, bottom;

    public:
        CenterBottomConstraint(std::shared_ptr<Constraint> top, std::shared_ptr<Constraint> height, std::shared_ptr<Constraint> bottom)
            :top(top), height(height), bottom(bottom) {
            dependencies.addAll({ this->top.get(), this->height.get(), this->bottom.get() });
        }

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (bottom->Value + top->Value + height->Value) / 2;
        }
    };

    class HeightBottomConstraint:public Constraint {
    private:
        Constraint* height, * bottom;

    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = bottom->Value - height->Value;
        }
    };
}