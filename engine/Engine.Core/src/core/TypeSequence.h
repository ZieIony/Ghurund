#pragma once

#include "core/string/FixedString.h"

#include <stdint.h>
#include <compare>

namespace Ghurund::Core {
    /**
     * @brief A sequence of values of type T increasing for each call.
     * @tparam Owner A type to identify template concretization.
     * @tparam T The type of the provided value.
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
     * @brief Provides increasing values of type T for each new Args combination.
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

    /**
     * @brief A sequence of values of type T increasing for each call. A new sequence is generated for each new specified name.
     * @tparam Owner A type to identify template concretization.
     * @tparam T The type of the provided value.
     * @tparam name The name of this sequence.
    */
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

    /**
     * @brief Provides increasing values of type T for each new specified name and Args combination.
     * @tparam Owner
     * @tparam T
     * @tparam ...Args
     * @tparam name The name of this sequence.
    */
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