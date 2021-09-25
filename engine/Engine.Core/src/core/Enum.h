#pragma once

#include "Noncopyable.h"
#include "core/collection/Map.h"
#include "core/string/String.h"

namespace Ghurund::Core {

    template<class Type, class Type2>
    class Enum;

    template<class Type, class Type2>
    class EnumValues:public Noncopyable {
    private:
        Map<Type, Type2*> values;
        Map<AString, Type2*> valuesByName;

        EnumValues(const std::initializer_list<const Type2*> list) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                values.set((*it)->Value, (Type2*)(*it));
                valuesByName.set((*it)->Name, (Type2*)(*it));
            }
        }

    public:
        friend class Enum<Type, Type2>;
        friend typename Type2;

        inline const Type2& operator[](const Type& key) const {
            return *values.get(key);
        }

        inline const Type2& operator[](const size_t index) const {
            return *values.getValue(index);
        }

        inline const Type2& operator[](const AString& name) const {
            return *valuesByName.get(name);
        }

        inline size_t getSize() const {
            return values.Size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline Type2* begin() {
            return values.begin();
        }

        inline Type2* begin() const {
            return values.begin();
        }

        inline Type2* end() {
            return values.end();
        }

        inline Type2* end() const {
            return values.end();
        }
    };

    template<class EnumValueType, class EnumType>
    class Enum {
    private:
		EnumValueType value;
        const AString name;

    protected:
        Enum(EnumValueType value, const AString& name):name(name) {
            this->value = value;
        }

    public:
        inline EnumValueType getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) EnumValueType Value;

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        inline bool operator==(const Enum& type) const {
            return this->value == type.value;
        }

        inline bool operator==(const Enum& type) {
            return this->value == type.value;
        }
    };
}