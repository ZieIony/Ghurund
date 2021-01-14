#pragma once

#include <functional>

namespace Ghurund {
    class Property {
    private:
        const char* typeName;
        const char* propertyName;

    public:
        Property(const char* typeName, const char* propertyName):typeName(typeName), propertyName(propertyName) {}

        inline const char* getName() const {
            return propertyName;
        }

        __declspec(property(get = getName)) const char* Name;

        inline const char* getTypeName() const {
            return typeName;
        }

        __declspec(property(get = getTypeName)) const char* TypeName;

        virtual void get(void* owner, void** value) = 0;

        virtual void set(void* owner, void* value) = 0;

        virtual bool isReadOnly() const = 0;

        __declspec(property(get = isReadOnly)) bool ReadOnly;
    };

    template<class OwnerType, class PropType>
    class TypedProperty:public Property {
    private:
        std::function<void(OwnerType&, typename std::remove_const<PropType>::type&)> getter;
        std::function<void(OwnerType&, PropType&)> setter;
        bool readOnly;

    public:
        TypedProperty(const char* typeName, const char* propertyName, std::function<void(OwnerType&, typename std::remove_const<PropType>::type&)> getter, std::function<void(OwnerType&, const PropType&)> setter):
            Property(typeName, propertyName), getter(getter), setter(setter), readOnly(false) {}

        TypedProperty(const char* typeName, const char* propertyName, std::function<void(OwnerType&, typename std::remove_const<PropType>::type&)> getter):
            Property(typeName, propertyName), getter(getter), readOnly(true) {}

        virtual void get(void* owner, void** value) {
            typename std::remove_const<PropType>::type v;
            getter(*(OwnerType*)owner, v);
            *(typename std::remove_const<PropType>::type*)value = v;
        }

        void get(OwnerType& owner, PropType& value) {
            getter(owner, value);
        }

        virtual void set(void* owner, void* value) {
            setter(*(OwnerType*)owner, (PropType&)value);
        }

        void set(OwnerType& owner, PropType& value) {
            setter(owner, value);
        }

        virtual bool isReadOnly() const override {
            return readOnly;
        }
    };
}