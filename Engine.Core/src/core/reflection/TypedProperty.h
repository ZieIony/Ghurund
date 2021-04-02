#pragma once

#include "Property.h"

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

    template<class OwnerType>
    class BoolProperty:public TypedProperty<OwnerType, bool> {
    public:
        BoolProperty(const char* propertyName, TypedProperty<OwnerType, bool>::Getter getter, TypedProperty<OwnerType, bool>::Setter setter = nullptr)
            :TypedProperty<OwnerType, bool>("bool", propertyName, getter, setter) {}
    };

    template<class OwnerType>
    class UInt32Property:public TypedProperty<OwnerType, uint32_t> {
    public:
        UInt32Property(const char* propertyName, TypedProperty<OwnerType, uint32_t>::Getter getter, TypedProperty<OwnerType, uint32_t>::Setter setter = nullptr)
            :TypedProperty<OwnerType, uint32_t>("uint32", propertyName, getter, setter) {}
    };

    template<class OwnerType>
    class FloatProperty:public TypedProperty<OwnerType, float> {
    public:
        FloatProperty(const char* propertyName, TypedProperty<OwnerType, float>::Getter getter, TypedProperty<OwnerType, float>::Setter setter = nullptr)
            :TypedProperty<OwnerType, uint32_t>("float", propertyName, getter, setter) {}
    };
}