#pragma once

#include "core/SharedPointer.h"
#include "ui/layout/constraint/Side.h"
#include "ui/Orientation.h"
#include "core/collection/Set.h"

namespace Ghurund::UI {
    class Control;
    class ControlGroup;
    class Guide;

    using namespace Ghurund::Core;

    class Constraint {
    protected:
        float value = 0.0f;
        bool skipDependencies = false;
        Set<Constraint*> dependencies;

    public:
        Constraint() {}

        Constraint(float initial, bool skipDependencies):value(initial), skipDependencies(skipDependencies) {}

        virtual ~Constraint()// = 0 
        {}

        virtual bool isConstant() const {
            return false;
        }

        __declspec(property(get = isConstant)) bool Constant;

        virtual void resolve(Control& control) {}

        virtual void evaluate() {}

        Set<Constraint*>& getDependencies() {
            return dependencies;
        }

        __declspec(property(get = getDependencies)) Set<Constraint*>& Dependencies;

        inline float getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) float Value;

        inline bool canSkipDependencies() const {
            return skipDependencies;
        }

        __declspec(property(get = canSkipDependencies)) bool CanSkipDependencies;
    };

    class LeftWidthConstraint:public Constraint {
    private:
        Constraint* left, * width;

    public:
        virtual void resolve(Control& control) override;

        virtual void evaluate() override {
            value = left->Value + width->Value;
        }
    };

    class RightWidthConstraint:public Constraint {
    private:
        Constraint* right, * width;

    public:
        virtual void resolve(Control& control) override;

        virtual void evaluate() override {
            value = right->Value - width->Value;
        }
    };

    class TopHeightConstraint:public Constraint {
    private:
        Constraint* top, * height;

    public:
        virtual void resolve(Control& control) override;

        virtual void evaluate() override {
            value = top->Value + height->Value;
        }
    };

    class BottomHeightConstraint:public Constraint {
    private:
        Constraint* bottom, * height;

    public:
        virtual void resolve(Control& control) override;

        virtual void evaluate() override {
            value = bottom->Value - height->Value;
        }
    };
}
