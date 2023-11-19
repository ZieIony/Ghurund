#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class ValueConstraint:public Constraint {
    public:
        ValueConstraint():Constraint(true, true) {}

        ValueConstraint(float value = 0.0f):Constraint(true, true) {
            this->value = value;
        }

        inline void setValue(float value) {
            this->value = value;
        }

        __declspec(property(get = getValue, put = setValue)) float Value;

        virtual Object* clone() const {
            return ghnew ValueConstraint(*this);
        }
    };

}