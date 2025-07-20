#pragma once

#include "Constraint.h"

namespace Ghurund::UI {

    class ValueConstraint:public Constraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ValueConstraint::GET_TYPE();
#pragma endregion

    protected:
        ~ValueConstraint() {}

    public:
        ValueConstraint():Constraint(ConstraintOptions::IS_CONSTANT) {}

        ValueConstraint(float value):Constraint(ConstraintOptions::IS_CONSTANT) {
            this->value = value;
            evaluated = true;
        }

        inline void setValue(float value) {
            this->value = value;
            evaluated = true;
        }

        __declspec(property(get = getValue, put = setValue)) float Value;

        virtual float getPreferredMax() const {
            return value;
        }

        virtual ValueConstraint* clone() const {
            return ghnew ValueConstraint(*this);
        }
    };

}