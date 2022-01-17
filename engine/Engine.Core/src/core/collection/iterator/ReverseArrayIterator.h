#pragma once

#include <iterator>

namespace Ghurund::Core {
    template<typename Type>
    class ReverseArrayIterator {
    private:
        Type* v;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ReverseArrayIterator(): v(nullptr) {}
        ReverseArrayIterator(Type* other): v(other) {}
        ReverseArrayIterator(const ReverseArrayIterator& other): v(other.v) {}

        inline ReverseArrayIterator& operator=(Type* v) { this.v = v; return *this; }
        inline ReverseArrayIterator& operator=(const ReverseArrayIterator& other) { v = other.v; return *this; }

        inline Type& operator*() { return *v; }
        inline Type& operator*() const { return *v; }
        inline Type* operator->() const { return v; }

        inline ReverseArrayIterator& operator++() { --v; return *this; }
        inline ReverseArrayIterator& operator--() { ++v; return *this; }
        inline ReverseArrayIterator operator++(int) { ReverseArrayIterator copy(*this); --v; return copy; }
        inline ReverseArrayIterator operator--(int) { ReverseArrayIterator copy(*this); ++v; return copy; }

        inline difference_type operator-(const ReverseArrayIterator& other) const { return other.v - v; }
        inline ReverseArrayIterator operator+(difference_type other) const { return ReverseArrayIterator(v - other); }
        inline ReverseArrayIterator operator-(difference_type other) const { return ReverseArrayIterator(v + other); }
        friend inline ReverseArrayIterator operator+(difference_type lhs, const ReverseArrayIterator& rhs) { return ReverseArrayIterator(rhs.v - lhs); }

        inline ReverseArrayIterator& operator+=(difference_type other) { v -= other; return *this; }
        inline ReverseArrayIterator& operator-=(difference_type other) { v += other; return *this; }

        constexpr std::strong_ordering operator<=>(const ReverseArrayIterator& other) const noexcept {
            return other.v <=> v;
        }

        constexpr bool operator==(const ReverseArrayIterator& other) const noexcept {
            return v == other.v;
        }

        constexpr bool operator!=(const ReverseArrayIterator& other) const noexcept {
            return v != other.v;
        }

        inline Type& operator[](difference_type other) const { return v[other]; }
    };

    template<typename Type>
    class ConstReverseArrayIterator {
    private:
        Type* v;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ConstReverseArrayIterator(): v(nullptr) {}
        ConstReverseArrayIterator(Type* other): v(other) {}
        ConstReverseArrayIterator(const ConstReverseArrayIterator& other): v(other.v) {}
        ConstReverseArrayIterator(const ReverseArrayIterator<Type>& other): v(other.v) {}

        inline ConstReverseArrayIterator& operator=(Type* v) { this.v = v; return *this; }
        inline ConstReverseArrayIterator& operator=(const ConstReverseArrayIterator& other) { v = other.v; return *this; }

        inline Type& operator*() const { return *v; }
        inline Type* operator->() const { return v; }

        inline ConstReverseArrayIterator& operator++() { --v; return *this; }
        inline ConstReverseArrayIterator& operator--() { ++v; return *this; }
        inline ConstReverseArrayIterator operator++(int) { ConstReverseArrayIterator copy(*this); --v; return copy; }
        inline ConstReverseArrayIterator operator--(int) { ConstReverseArrayIterator copy(*this); ++v; return copy; }

        inline difference_type operator-(const ConstReverseArrayIterator& other) const { return other.v - v; }
        inline ConstReverseArrayIterator operator+(difference_type other) const { return ConstReverseArrayIterator(v - other); }
        inline ConstReverseArrayIterator operator-(difference_type other) const { return ConstReverseArrayIterator(v + other); }
        friend inline ConstReverseArrayIterator operator+(difference_type lhs, const ConstReverseArrayIterator& rhs) { return ConstReverseArrayIterator(rhs.v - lhs); }

        inline ConstReverseArrayIterator& operator+=(difference_type other) { v -= other; return *this; }
        inline ConstReverseArrayIterator& operator-=(difference_type other) { v += other; return *this; }

        constexpr std::strong_ordering operator<=>(const ConstReverseArrayIterator& other) const noexcept {
            return other.v <=> v;
        }

        constexpr bool operator==(const ConstReverseArrayIterator& other) const noexcept {
            return v == other.v;
        }

        constexpr bool operator!=(const ConstReverseArrayIterator& other) const noexcept {
            return v != other.v;
        }

        inline Type& operator[](difference_type other) const { return v[other]; }
    };
}