#pragma once

#include "core/string/FixedString.h"

#include <stdint.h>
#include <compare>

namespace Ghurund::Core {
    /**
     * @brief Provides increasing values of type T for each call
     * @tparam Owner a type to identify template concretization
     * @tparam T type of the provided value
    */
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

    /**
     * @brief Provides increasing values of type T for each new Args combination
     * @tparam Owner 
     * @tparam T 
     * @tparam ...Args 
    */
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