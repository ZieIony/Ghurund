#pragma once

#include "core/object/RefCountedObject.h"
#include "core/string/String.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ParameterCollection;

    class Parameter: public RefCountedObject {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Parameter::GET_TYPE();
#pragma endregion

    protected:
        const AString name;
        bool isEmpty = true;

        Parameter(const Parameter& other):name(other.name), isEmpty(other.isEmpty) {}

    public:
        Parameter(const AString& name):name(name) {}

        const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        inline bool getIsEmpty() const {
            return isEmpty;
        }

        __declspec(property(get = getIsEmpty)) bool IsEmpty;
  
        inline void reset() {
            isEmpty = true;
        }
    };
}