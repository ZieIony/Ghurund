#pragma once

#include "ParameterId.h"
#include "core/Pointer.h"
#include "core/string/AString.h"
#include "editor/ObservableObject.h"

namespace Ghurund {
    class Parameter: public Pointer, public ObservableObject {
    protected:
        const AString constantName;
        const ParameterType& type;
        bool empty;

        static const Ghurund::Type& GET_TYPE();

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}