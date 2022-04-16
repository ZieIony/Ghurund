#include "ghuipch.h"
#include "RatioConstraint.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
    void RatioConstraint::evaluate() {
        value = constraint->Value * ratio;
    }

    bool RatioConstraint::isConstant() const {
        return constraint->Constant;
    }
}