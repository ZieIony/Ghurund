#pragma once

#include "Parameter.h"

namespace Ghurund {

    class ValueParameter:public Parameter {
    private:
        void* data;
        void* value = nullptr;
        void* defaultValue = nullptr;

    public:
        ValueParameter(const char* constantName, const ParameterType& type):Parameter(constantName, type) {
            this->data = ghnew uint8_t[type.Size];
            memset(this->data, 0, type.Size);
            value = defaultValue;
            empty = true;
        }

        ValueParameter(const char* constantName, const ParameterType& type, const void* value):Parameter(constantName, type) {
            this->data = ghnew uint8_t[type.Size];
            memcpy(this->data, value, type.Size);
            this->value = data;
            empty = false;
        }

        ~ValueParameter() {
            delete[] data;
        }

        inline void* getValue() const {
            return value;
        }

        void setValue(const void* value) {
            this->value = data;
            empty = false;
            memcpy(this->value, value, type.Size);
        }

        void clearValue() {
            empty = true;
            value = defaultValue;
        }

        __declspec(property(get = getValue, put = setValue)) const void* Value;

        inline void* getDefaultValue() {
            return defaultValue;
        }

        void setDefaultValue(void* value) {
            defaultValue = value;
            if (!this->value)
                this->value = defaultValue;
        }

        __declspec(property(get = getDefaultValue, put = setDefaultValue)) void* DefaultValue;
    };

}