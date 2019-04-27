#pragma once

#include "Parameter.h"
#include "core/Pointer.h"

namespace Ghurund {

    class ObjectParameter:public Parameter {
    private:
        Pointer* value;

    public:
        ObjectParameter(const ASCIIString& name):Parameter(name, ParameterType::OBJECT) {
            this->value = nullptr;
        }

        ObjectParameter(const ASCIIString& name, Pointer* value):Parameter(name, ParameterType::OBJECT) {
            this->value = value;
            value->addReference();
        }

        ~ObjectParameter() {
            if (value)
                value->release();
        }

        inline Pointer* getValue() {
            return value;
        }

        void setValue(Pointer* value) {
            setPointer(this->value, value);
            notifyObjectChanged();
        }

        __declspec(property(get = getValue, put = setValue)) Pointer* Value;
    };
}