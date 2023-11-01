#pragma once

#include <iterator>

namespace Ghurund::Core {
	template<typename Type, typename NodeType>
	class TreeNodeIterator {
	private:
		NodeType* node;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::remove_cv_t<Type>;
		using pointer = Type*;
		using reference = Type&;

		TreeNodeIterator(): node(nullptr) {}
		TreeNodeIterator(NodeType* other): node(other) {}
		TreeNodeIterator(const TreeNodeIterator& other): node(other.node) {}

		inline TreeNodeIterator& operator=(NodeType* node) { this.node = node; return *this; }
		inline TreeNodeIterator& operator=(const TreeNodeIterator& other) { node = other.node; return *this; }

		inline Type& operator*() { return node->data; }
		inline Type& operator*() const { return node->data; }
		inline Type* operator->() const { return &node->data; }

		// prefix ++it;
		inline TreeNodeIterator& operator++() { node = node->getNext(); return *this; }
		inline TreeNodeIterator& operator--() { node = node->getPrevious(); return *this; }
		// postfix it++
		inline TreeNodeIterator operator++(int) { TreeNodeIterator copy(*this); node = node->getNext(); return copy; }
		inline TreeNodeIterator operator--(int) { TreeNodeIterator copy(*this); node = node->getPrevious(); return copy; }

		constexpr bool operator==(const TreeNodeIterator& other) const noexcept {
            return node == other.node;
		}

		constexpr bool operator!=(const TreeNodeIterator& other) const noexcept {
            return node != other.node;
		}
	};

	template<typename Type, typename NodeType>
	class ConstTreeNodeIterator {
	private:
		NodeType* node;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::remove_cv_t<Type>;
		using pointer = Type*;
		using reference = Type&;

		ConstTreeNodeIterator(): node(nullptr) {}
		ConstTreeNodeIterator(NodeType* other): node(other) {}
		ConstTreeNodeIterator(const ConstTreeNodeIterator& other): node(other.node) {}
		ConstTreeNodeIterator(const TreeNodeIterator<Type, NodeType>& other): node(other.node) {}

		inline ConstTreeNodeIterator& operator=(NodeType* node) { this.node = node; return *this; }
		inline ConstTreeNodeIterator& operator=(const ConstTreeNodeIterator& other) { node = other.node; return *this; }

		inline Type& operator*() const { return node->data; }
		inline Type* operator->() const { return &node->data; }

		inline ConstTreeNodeIterator& operator++() { node = node->getNext(); return *this; }
		inline ConstTreeNodeIterator& operator--() { node = node->getPrevious(); return *this; }
		inline ConstTreeNodeIterator operator++(int) { ConstTreeNodeIterator copy(*this); node = node->getNext(); return copy; }
		inline ConstTreeNodeIterator operator--(int) { ConstTreeNodeIterator copy(*this); node = node->getPrevious(); return copy; }

		constexpr bool operator==(const ConstTreeNodeIterator& other) const noexcept {
            return node == other.node;
		}

		constexpr bool operator!=(const ConstTreeNodeIterator& other) const noexcept {
            return node != other.node;
		}
	};
}