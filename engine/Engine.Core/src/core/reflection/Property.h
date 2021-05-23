#pragma once

namespace Ghurund {
    template<class OwnerType, class PropType>
    class TypedProperty;

    class Property {
    private:
        static const inline char* DEFAULT_GROUP = "default";

        const char* typeName;
        const char* propertyName;
        const char* group;

    protected:
        bool readOnly;

    public:
        Property(const char* typeName, const char* propertyName, const char* group = DEFAULT_GROUP, bool readOnly = false):typeName(typeName), propertyName(propertyName), group(group), readOnly(readOnly) {}

        virtual ~Property() = 0 {}

        inline const char* getName() const {
            return propertyName;
        }

        __declspec(property(get = getName)) const char* Name;

        inline const char* getTypeName() const {
            return typeName;
        }

        __declspec(property(get = getTypeName)) const char* TypeName;

        inline bool isReadOnly() const {
            return readOnly;
        }

        __declspec(property(get = isReadOnly)) bool ReadOnly;

        template<class OwnerType, class PropType>
        inline PropType get(OwnerType& owner) {
            return ((TypedProperty<OwnerType, PropType>*)this)->get(owner);
        }

        template<class OwnerType, class PropType>
        inline void set(OwnerType& owner, PropType value) {
            ((TypedProperty<OwnerType, PropType>*)this)->set(owner, value);
        }
    };
}