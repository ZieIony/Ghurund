#pragma once

#include <iterator>

namespace Ghurund::Core {
    template<typename Type, typename NodeType>
    class ReverseTreeNodeIterator {
    private:
        NodeType* node;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ReverseTreeNodeIterator(): node(nullptr) {}
        ReverseTreeNodeIterator(NodeType* other): node(other) {}
        ReverseTreeNodeIterator(const ReverseTreeNodeIterator& other): node(other.node) {}

        inline ReverseTreeNodeIterator& operator=(NodeType* node) { this.node = node; return *this; }
        inline ReverseTreeNodeIterator& operator=(const ReverseTreeNodeIterator& other) { node = other.node; return *this; }

        inline Type& operator*() { return node; }
        inline Type& operator*() const { return node; }
        inline Type* operator->() const { return &node; }

        inline ReverseTreeNodeIterator& operator++() { node = node->getPrevious(); return *this; }
        inline ReverseTreeNodeIterator& operator--() { node = node->getNext(); return *this; }
        inline ReverseTreeNodeIterator operator++(int) { ReverseTreeNodeIterator copy(*this); node = node->getPrevious(); return copy; }
        inline ReverseTreeNodeIterator operator--(int) { ReverseTreeNodeIterator copy(*this); node = node->getNext(); return copy; }

        constexpr bool operator==(const ReverseTreeNodeIterator& other) const noexcept {
            return node == other.node;
        }

        constexpr bool operator!=(const ReverseTreeNodeIterator& other) const noexcept {
            return node != other.node;
        }
    };

    template<typename Type, typename NodeType>
    class ConstReverseTreeNodeIterator {
    private:
        NodeType* node;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::remove_cv_t<Type>;
        using pointer = Type*;
        using reference = Type&;

        ConstReverseTreeNodeIterator(): node(nullptr) {}
        ConstReverseTreeNodeIterator(NodeType* other): node(other) {}
        ConstReverseTreeNodeIterator(const ConstReverseTreeNodeIterator& other): node(other.node) {}
        ConstReverseTreeNodeIterator(const ReverseTreeNodeIterator<Type, NodeType>& other): node(other.node) {}

        inline ConstReverseTreeNodeIterator& operator=(NodeType* node) { this.node = node; return *this; }
        inline ConstReverseTreeNodeIterator& operator=(const ConstReverseTreeNodeIterator& other) { node = other.node; return *this; }

        inline Type& operator*() const { return node; }
        inline Type* operator->() const { return &node; }

        inline ConstReverseTreeNodeIterator& operator++() { node = node->getPrevious(); return *this; }
        inline ConstReverseTreeNodeIterator& operator--() { node = node->getNext(); return *this; }
        inline ConstReverseTreeNodeIterator operator++(int) { ConstReverseTreeNodeIterator copy(*this); node = node->getPrevious(); return copy; }
        inline ConstReverseTreeNodeIterator operator--(int) { ConstReverseTreeNodeIterator copy(*this); node = node->getNext(); return copy; }

        constexpr bool operator==(const ConstReverseTreeNodeIterator& other) const noexcept {
            return node == other.node;
        }

        constexpr bool operator!=(const ConstReverseTreeNodeIterator& other) const noexcept {
            return node != other.node;
        }
    };
}