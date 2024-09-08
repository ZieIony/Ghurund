#pragma once

#include <iterator>

namespace Ghurund::Core {
    template<typename Type>
    class ArrayIterator {
    private:
        Type* v;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ArrayIterator(): v(nullptr) {}
        ArrayIterator(Type* other): v(other) {}
        ArrayIterator(const ArrayIterator& other): v(other.v) {}

        inline ArrayIterator& operator=(Type* v) { this.v = v; return *this; }
        inline ArrayIterator& operator=(const ArrayIterator& other) { v = other.v; return *this; }

        inline Type& operator*() { return *v; }
        inline Type& operator*() const { return *v; }
        inline Type* operator->() const { return v; }

        // prefix ++it;
        inline ArrayIterator& operator++() { ++v; return *this; }
        inline ArrayIterator& operator--() { --v; return *this; }
        // postfix it++
        inline ArrayIterator operator++(int) { ArrayIterator copy(*this); ++v; return copy; }
        inline ArrayIterator operator--(int) { ArrayIterator copy(*this); --v; return copy; }

        inline difference_type operator-(const ArrayIterator& other) const { return v - other.v; }
        inline ArrayIterator operator+(difference_type other) const { return ArrayIterator(v + other); }
        inline ArrayIterator operator-(difference_type other) const { return ArrayIterator(v - other); }
        friend inline ArrayIterator operator+(difference_type lhs, const ArrayIterator& rhs) { return ArrayIterator(lhs + rhs.v); }

        inline ArrayIterator& operator+=(difference_type other) { v += other; return *this; }
        inline ArrayIterator& operator-=(difference_type other) { v -= other; return *this; }

        constexpr std::strong_ordering operator<=>(const ArrayIterator& other) const noexcept {
            return v <=> other.v;
        }

        constexpr bool operator==(const ArrayIterator& other) const noexcept {
            return v == other.v;
        }

        constexpr bool operator!=(const ArrayIterator& other) const noexcept {
            return v != other.v;
        }

        inline Type& operator[](difference_type other) const { return v[other]; }
    };

    template<typename Type>
    class ConstArrayIterator {
    private:
        Type* v;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ConstArrayIterator(): v(nullptr) {}
        ConstArrayIterator(Type* other): v(other) {}
        ConstArrayIterator(const ConstArrayIterator& other): v(other.v) {}
        ConstArrayIterator(const ArrayIterator<Type>& other): v(other.v) {}

        inline ConstArrayIterator& operator=(Type* v) { this.v = v; return *this; }
        inline ConstArrayIterator& operator=(const ConstArrayIterator& other) { v = other.v; return *this; }

        inline Type& operator*() const { return *v; }
        inline Type* operator->() const { return v; }

        inline ConstArrayIterator& operator++() { ++v; return *this; }
        inline ConstArrayIterator& operator--() { --v; return *this; }
        inline ConstArrayIterator operator++(int) { ConstArrayIterator copy(*this); ++v; return copy; }
        inline ConstArrayIterator operator--(int) { ConstArrayIterator copy(*this); --v; return copy; }

        inline difference_type operator-(const ConstArrayIterator& other) const { return v - other.v; }
        inline ConstArrayIterator operator+(difference_type other) const { return ConstArrayIterator(v + other); }
        inline ConstArrayIterator operator-(difference_type other) const { return ConstArrayIterator(v - other); }
        friend inline ConstArrayIterator operator+(difference_type lhs, const ConstArrayIterator& rhs) { return ConstArrayIterator(lhs + rhs.v); }

        inline ConstArrayIterator& operator+=(difference_type other) { v += other; return *this; }
        inline ConstArrayIterator& operator-=(difference_type other) { v -= other; return *this; }

        constexpr std::strong_ordering operator<=>(const ConstArrayIterator& other) const noexcept {
            return v <=> other.v;
        }

        constexpr bool operator==(const ConstArrayIterator& other) const noexcept {
            return v == other.v;
        }

        constexpr bool operator!=(const ConstArrayIterator& other) const noexcept {
            return v != other.v;
        }

        inline Type& operator[](difference_type other) const { return v[other]; }
    };
}