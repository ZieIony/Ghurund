#pragma once

#include "Parameter.h"
#include "resource/Resource.h"

namespace Ghurund {

    class ResourceParameter:public Parameter {
    private:
        Resource* value;

    public:
        ResourceParameter(const ASCIIString& name, const ParameterValueType& type):Parameter(name, type) {
            this->value = nullptr;
        }

        ResourceParameter(const ASCIIString& name, Resource* value, const ParameterValueType& type):Parameter(name, type) {
            this->value = value;
            value->addReference();
        }

        ~ResourceParameter() {
            if (value)
                value->release();
        }

        inline Resource* getValue() {
            return value;
        }

        void setValue(Resource* value) {
            setPointer(this->value, value);
            notifyObjectChanged();
        }

        __declspec(property(get = getValue, put = setValue)) Resource* Value;
    };
}