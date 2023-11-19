#pragma once

#include "MinMaxConstraint.h"
#include "core/SharedPointer.h"

namespace Ghurund::UI {

    class WrapWidthConstraint:public MinMaxConstraint {
    private:
        Control* control = nullptr;

    protected:
        WrapWidthConstraint(const WrapWidthConstraint& other):MinMaxConstraint(other), control(other.control) {}

        virtual bool equalsImpl(const Object& other) const override;

    public:
        WrapWidthConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;

        virtual Object* clone() const {
            return ghnew WrapWidthConstraint(*this);
        }
    };

    class WrapHeightConstraint:public MinMaxConstraint {
    private:
        Control* control = nullptr;

    protected:
        WrapHeightConstraint(const WrapHeightConstraint& other):MinMaxConstraint(other), control(other.control) {}
  
        virtual bool equalsImpl(const Object& other) const override;

    public:
        WrapHeightConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;

        virtual Object* clone() const {
            return ghnew WrapHeightConstraint(*this);
        }
    };
}