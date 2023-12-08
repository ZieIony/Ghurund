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

        inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

    protected:
        ~ValueConstraint() {}

    public:
        ValueConstraint():Constraint(true, false) {}

        ValueConstraint(float value):Constraint(true, false) {
            this->value = value;
            evaluated = true;
        }

        inline void setValue(float value) {
            this->value = value;
            evaluated = true;
        }

        __declspec(property(get = getValue, put = setValue)) float Value;

        virtual Object* clone() const {
            return ghnew ValueConstraint(*this);
        }
    };

}