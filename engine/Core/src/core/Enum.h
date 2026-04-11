#pragma once

#include "core/collection/Map.h"
#include "core/string/String.h"
#include "core/exception/Exceptions.h"
#include "core/object/Noncopyable.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {

    template<class Type, class Type2>
    class Enum;

    template<class Type, class Type2>
    class EnumValues:public Noncopyable {
    private:
        mutable List<std::reference_wrapper<const Type2>> values;

        inline void add(const std::reference_wrapper<const Type2> value) const {
            values.add(value);
        }

    public:
        using iterator = List<std::reference_wrapper<const Type2>>::iterator;
        using const_iterator = List<std::reference_wrapper<const Type2>>::const_iterator;

        friend class Enum<Type, Type2>;
        friend typename Type2;

        inline const Type2& operator[](const size_t index) const {
            return values.get(index);
        }

        inline size_t getSize() const {
            return values.Size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline iterator begin() {
            return values.begin();
        }

        inline const_iterator begin() const {
            return ((const List<std::reference_wrapper<const Type2>>&)values).begin();
        }

        inline iterator end() {
            return values.end();
        }

        inline const_iterator end() const {
            return ((const List<std::reference_wrapper<const Type2>>&)values).end();
        }
    };

    template<class EnumValueType, class EnumType>
    class Enum {
    private:
		EnumValueType value;
        AString name;

    protected:
        Enum(EnumValueType value, const AString& name):name(name), value(value) {
            VALUES.add(std::reference_wrapper<EnumType>(*(EnumType*)this));
        }

    public:
        static inline const EnumValues<EnumValueType, EnumType> VALUES;

        static inline const EnumType& fromValue(EnumValueType value) {
            for (auto& v : VALUES) {
                if (v.get().Value == value)
                    return v.get();
            }
            throw InvalidParamException();
        }

        static inline const EnumType& fromName(const AString& name) {
            for (auto& v : VALUES) {
                if (v.get().Name == name)
                    return v.get();
            }
            throw InvalidParamException();
        }

        Enum(const Enum& other):value(other.value), name(other.name) {}

        Enum(Enum&& other) noexcept:value(other.value), name(std::move(other.name)) {}

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

        Enum& operator=(const Enum& other) {
            if (this == &other)
                return *this;
            value = other.value;
            name = other.name;
            return *this;
        }

        Enum& operator=(Enum&& other) noexcept {
            if (this == &other)
                return *this;
            value = std::move(other.value);
            name = std::move(other.name);
            return *this;
        }

        inline auto operator<=>(const Enum& other) const {
			return value <=> other.value;
        }
    };
}
