#pragma once

#include "Property.h"

#include <functional>

namespace Ghurund {
    template<class OwnerType, class PropType>
    class TypedProperty:public Property {
    protected:
        typedef std::function<PropType(OwnerType&)> Getter;
        typedef std::function<void(OwnerType&, PropType)> Setter;

    private:
        Getter getter = nullptr;
        Setter setter = nullptr;

    public:
        TypedProperty(const char* typeName, const char* propertyName, Getter getter, Setter setter = nullptr):Property(typeName, propertyName) {
            this->getter = getter;
            this->setter = setter;
            readOnly = !setter;
        }

        inline PropType get(OwnerType& owner) {
            return getter(owner);
        }

        inline void set(OwnerType& owner, PropType value) {
            setter(owner, value);
        }
    };
}