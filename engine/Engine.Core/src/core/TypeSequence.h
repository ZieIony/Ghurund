#pragma once

#include <stdint.h>
#include <compare>

namespace Ghurund::Core {
    template<typename Owner, typename T>
    class Sequence {
    private:
        Sequence() {}
    public:
        static T next() {
            static T value{};
            return value++;
        }
    };

    template<typename Owner, typename T, typename... Args>
    class TypeSequence {
    private:
        TypeSequence() {}

    public:
        static T value() {
            static const T value = Sequence<Owner, T>::next();
            return value;
        }

        constexpr operator T() const {
            return value();
        }
    };

    template<size_t N>
    struct FixedString {
        char elems[N];

        constexpr FixedString(char const (&s)[N]) {
            std::copy_n(s, N, elems);
        }

        constexpr std::strong_ordering operator<=>(FixedString const&) const = default;
    };

    template<typename Owner, typename T, FixedString name>
    class NamedSequence {
    private:
        NamedSequence() {}
    public:
        static T next() {
            static T value{};
            return value++;
        }
    };

    template<typename Owner, typename T, FixedString name, typename... Args>
    class NamedTypeSequence {
    private:
        NamedTypeSequence() {}

    public:
        static T value() {
            static const T value = NamedSequence<Owner, T, name>::next();
            return value;
        }

        constexpr operator T() const {
            return value();
        }
    };
}