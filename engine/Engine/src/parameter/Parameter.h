#pragma once

#include "ParameterId.h"
#include "core/Pointer.h"
#include "core/string/String.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class Parameter: public Pointer {
    protected:
        const AString constantName;
        const ParameterType& type;
        bool empty = true;

    public:
        Parameter(const AString& constantName, const ParameterType& type):constantName(constantName), type(type) {}

        const ParameterType& getValueType() const {
            return type;
        }

        __declspec(property(get = getValueType)) const ParameterType& ValueType;

        const AString& getConstantName() const {
            return constantName;
        }

        __declspec(property(get = getConstantName)) const AString& ConstantName;

        bool isEmpty() const {
            return empty;
        }

        __declspec(property(get = isEmpty)) bool Empty;

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}