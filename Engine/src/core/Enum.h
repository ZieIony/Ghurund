#pragma once

#include "Noncopyable.h"
#include "collection/Map.h"

namespace Ghurund {

    template<class Type, class Type2>
    class Enum;

    template<class Type, class Type2>
    class EnumValues:public Noncopyable {
    private:
        Map<Type, Type2*> values;

        EnumValues(const std::initializer_list<const Type2*> list) {
            for (auto it = list.begin(); it != list.end(); ++it)
                values.set((*it)->Value, (Type2*)(*it));
        }

    public:
        friend class Enum<Type, Type2>;
        friend typename Type2;

        const Type2& operator[](const Type& key) {
            return *values.get(key);
        }

        const Type2& operator[](const size_t key) {
            return *values.getValue(key);
        }

        inline size_t getSize() const {
            return values.Size;
        }

        __declspec(property(get = getSize)) size_t Size;
    };

    template<class Type, class Type2>
    class Enum:public Noncopyable {
    private:
        Type value;
        const tchar* name;

    public:
        explicit Enum(Type value, const tchar* name) {
            this->value = value;
            this->name = name;
        }

        static EnumValues<Type, Type2> VALUES;

        EnumValues<Type, Type2>& getValues() const {
            return VALUES;
        }

        __declspec(property(get = getValues)) EnumValues<Type, Type2>& Values;

        Type getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) Type Value;

        const tchar* getName() const {
            return name;
        }

        __declspec(property(get = getName)) const tchar* Name;

        bool operator==(const Enum& type) const {
            return this->value == type.value;
        }

        bool operator==(const Enum& type) {
            return this->value == type.value;
        }
    };
}