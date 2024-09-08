#pragma once

#include <iterator>

namespace Ghurund::Core {
    template<typename Type, typename NodeType>
    class ListNodeIterator {
    private:
        NodeType* node;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ListNodeIterator(): node(nullptr) {}
        ListNodeIterator(NodeType* other): node(other) {}
        ListNodeIterator(const ListNodeIterator& other): node(other.node) {}

        inline ListNodeIterator& operator=(NodeType* node) { this.node = node; return *this; }
        inline ListNodeIterator& operator=(const ListNodeIterator& other) { node = other.node; return *this; }

        inline Type& operator*() { return node->data; }
        inline Type& operator*() const { return node->data; }
        inline Type* operator->() const { return &node->data; }

        // prefix ++it;
        inline ListNodeIterator& operator++() { node = node->next; return *this; }
        inline ListNodeIterator& operator--() { node = node->prev; return *this; }
        // postfix it++
        inline ListNodeIterator operator++(int) { ListNodeIterator copy(*this); node = node->next; return copy; }
        inline ListNodeIterator operator--(int) { ListNodeIterator copy(*this); node = node->prev; return copy; }

        constexpr bool operator==(const ListNodeIterator& other) const noexcept {
            return node == other.node;
        }

        constexpr bool operator!=(const ListNodeIterator& other) const noexcept {
            return node != other.node;
        }
    };

    template<typename Type, typename NodeType>
    class ConstListNodeIterator {
    private:
        NodeType* node;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ConstListNodeIterator(): node(nullptr) {}
        ConstListNodeIterator(NodeType* other): node(other) {}
        ConstListNodeIterator(const ConstListNodeIterator& other): node(other.node) {}
        ConstListNodeIterator(const ListNodeIterator<Type, NodeType>& other): node(other.node) {}

        inline ConstListNodeIterator& operator=(NodeType* node) { this.node = node; return *this; }
        inline ConstListNodeIterator& operator=(const ConstListNodeIterator& other) { node = other.node; return *this; }

        inline Type& operator*() const { return node->data; }
        inline Type* operator->() const { return &node->data; }

        inline ConstListNodeIterator& operator++() { node = node->next; return *this; }
        inline ConstListNodeIterator& operator--() { node = node->prev; return *this; }
        inline ConstListNodeIterator operator++(int) { ConstListNodeIterator copy(*this); node = node->next; return copy; }
        inline ConstListNodeIterator operator--(int) { ConstListNodeIterator copy(*this); node = node->prev; return copy; }

        constexpr bool operator==(const ConstListNodeIterator& other) const noexcept {
            return node == other.node;
        }

        constexpr bool operator!=(const ConstListNodeIterator& other) const noexcept {
            return node != other.node;
        }
    };
}