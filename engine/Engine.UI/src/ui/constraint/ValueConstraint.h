#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class ValueConstraint:public Constraint {
    public:
        ValueConstraint(float value):Constraint(value, true, true) {}
    };

}