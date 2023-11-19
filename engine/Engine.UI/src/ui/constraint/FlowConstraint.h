#pragma once

#include "MinMaxConstraint.h"

namespace Ghurund::UI {

    class FlowWidthConstraint:public MinMaxConstraint {
    public:
        FlowWidthConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;

        virtual Object* clone() const {
            return ghnew FlowWidthConstraint(*this);
        }
    };

    class FlowHeightConstraint:public MinMaxConstraint {
    public:
        FlowHeightConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;

        virtual Object* clone() const {
            return ghnew FlowHeightConstraint(*this);
        }
    };
}