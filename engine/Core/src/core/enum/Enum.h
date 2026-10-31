#pragma once

#include "Enum_templateDeclaration.h"
#include "EnumCollection.h"

#include "core/reflection/Type.h"
#include "core/string/String.h"

namespace Ghurund::Core {

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
        static inline const EnumCollection<EnumValueType, EnumType> VALUES;

        static inline const EnumType& fromValue(EnumValueType value) {
            for (auto& v : VALUES) {
                if (v.get().Value == value)
                    return v.get();
            }
            throw std::invalid_argument("enum value doesn't exist");
        }

        static inline const EnumType& fromName(const AString& name) {
            for (auto& v : VALUES) {
                if (v.get().Name == name)
                    return v.get();
            }
            throw std::invalid_argument(std::format("enum value \"{}\" doesn't exist", name.Data));
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
