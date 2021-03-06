#pragma once

namespace Ghurund {
    class Property {
    private:
        const char* typeName;
        const char* propertyName;

    protected:
        bool readOnly;

    public:
        Property(const char* typeName, const char* propertyName):typeName(typeName), propertyName(propertyName) {}

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
    };
}