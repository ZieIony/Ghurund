#pragma once

#include "Parameter.h"

namespace Ghurund {

    class ValueParameter:public Parameter {
    private:
        BYTE* value;

    public:
        ValueParameter(const ASCIIString& name, const ParameterValueType& type):Parameter(name, type) {
            this->value = ghnew BYTE[type.Size];
            memset(this->value, 0, type.Size);
        }

        ValueParameter(const ASCIIString& name, const void* value, const ParameterValueType& type):Parameter(name, type) {
            this->value = ghnew BYTE[type.Size];
            memcpy(this->value, value, type.Size);
        }

        ~ValueParameter() {
            delete[] value;
        }

        inline const void* getValue() const {
            return value;
        }

        void setValue(const void* value) {
            memcpy(this->value, value, type.Size);
            notifyObjectChanged();
        }

        __declspec(property(get = getValue, put = setValue)) const void* Value;
    };

}