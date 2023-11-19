#pragma once

#include "OffsetConstraint.h"
#include "ValueConstraint.h"
#include "core/math/MathUtils.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    class ParentLeftConstraint:public OffsetConstraint {
    };

    class ParentRightConstraint:public OffsetConstraint {
    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }

        virtual Object* clone() const {
            return ghnew ParentRightConstraint(*this);
        }
    };

    class ParentTopConstraint:public OffsetConstraint {
    };

    class ParentBottomConstraint:public OffsetConstraint {
    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = (*dependencies.begin())->Value + offset;
        }

        virtual Object* clone() const {
            return ghnew ParentBottomConstraint(*this);
        }
    };

    class ParentWidthConstraint:public MinMaxConstraint {
    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }

        virtual Object* clone() const {
            return ghnew ParentWidthConstraint(*this);
        }
    };

    class ParentHeightConstraint:public MinMaxConstraint {
    public:
        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override {
            value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
        }

        virtual Object* clone() const {
            return ghnew ParentHeightConstraint(*this);
        }
    };
}