#pragma once

#include <iterator>

namespace Ghurund::Core {
    template<typename Type, typename NodeType>
    class ReverseListNodeIterator {
    private:
        NodeType* node;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ReverseListNodeIterator(): node(nullptr) {}
        ReverseListNodeIterator(NodeType* other): node(other) {}
        ReverseListNodeIterator(const ReverseListNodeIterator& other): node(other.node) {}

        inline ReverseListNodeIterator& operator=(NodeType* node) { this.node = node; return *this; }
        inline ReverseListNodeIterator& operator=(const ReverseListNodeIterator& other) { node = other.node; return *this; }

        inline Type& operator*() { return node->data; }
        inline Type& operator*() const { return node->data; }
        inline Type* operator->() const { return &node->data; }

        inline ReverseListNodeIterator& operator++() { node = node->prev; return *this; }
        inline ReverseListNodeIterator& operator--() { node = node->next; return *this; }
        inline ReverseListNodeIterator operator++(int) { ReverseListNodeIterator copy(*this); node = node->prev; return copy; }
        inline ReverseListNodeIterator operator--(int) { ReverseListNodeIterator copy(*this); node = node->next; return copy; }

        constexpr bool operator==(const ReverseListNodeIterator& other) const noexcept {
            return node == other.node;
        }

        constexpr bool operator!=(const ReverseListNodeIterator& other) const noexcept {
            return node != other.node;
        }
    };

    template<typename Type, typename NodeType>
    class ConstReverseListNodeIterator {
    private:
        NodeType* node;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ConstReverseListNodeIterator(): node(nullptr) {}
        ConstReverseListNodeIterator(NodeType* other): node(other) {}
        ConstReverseListNodeIterator(const ConstReverseListNodeIterator& other): node(other.node) {}
        ConstReverseListNodeIterator(const ReverseListNodeIterator<Type, NodeType>& other): node(other.node) {}

        inline ConstReverseListNodeIterator& operator=(NodeType* node) { this.node = node; return *this; }
        inline ConstReverseListNodeIterator& operator=(const ConstReverseListNodeIterator& other) { node = other.node; return *this; }

        inline Type& operator*() const { return node->data; }
        inline Type* operator->() const { return &node->data; }

        inline ConstReverseListNodeIterator& operator++() { node = node->prev; return *this; }
        inline ConstReverseListNodeIterator& operator--() { node = node->next; return *this; }
        inline ConstReverseListNodeIterator operator++(int) { ConstReverseListNodeIterator copy(*this); node = node->prev; return copy; }
        inline ConstReverseListNodeIterator operator--(int) { ConstReverseListNodeIterator copy(*this); node = node->next; return copy; }

        constexpr bool operator==(const ConstReverseListNodeIterator& other) const noexcept {
            return node == other.node;
        }

        constexpr bool operator!=(const ConstReverseListNodeIterator& other) const noexcept {
            return node != other.node;
        }
    };
}