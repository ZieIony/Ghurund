#pragma once

#include "Common.h"
#include "Collection.h"
#include "core/allocation/SimpleAllocator.h"
#include "core/collection/iterator/TreeNodeIterator.h"
#include "core/collection/iterator/ReverseTreeNodeIterator.h"
#include "core/concepts/Iterable.h"

namespace Ghurund::Core {
	template<typename TraitsType, typename AllocatorType = SimpleAllocator>
	class Tree {
	private:
		TraitsType traits;

		using key_t = typename TraitsType::key_t;
		using value_t = typename TraitsType::value_t;
		using data_t = typename TraitsType::data_t;

		enum class NodeColor:uint8_t {
			RED, BLACK
		};

		struct Node {
			data_t data;
			NodeColor color = NodeColor::RED;
			Node* left = nullptr;
			Node* right = nullptr;
			Node* parent = nullptr;

			Node(const data_t& data):data(data) {}

			template<typename... Args>
			Node(const key_t& key, Args&&... args) : data(key, std::forward<Args>(args)...) {}

			inline bool isOnLeft() { return this == parent->left; }

			inline Node* getNext() {
				Node* node = this;
				if (node->right) {
					node = node->right;
					while (node->left)
						node = node->left;
				} else {
					while (node->parent && node->parent->right == node)
						node = node->parent;
					node = node->parent;
				}
				return node;
			}

			__declspec(property(get = getNext)) Node* Next;

			inline Node* getPrevious() {
				Node* node = this;
				if (node->left) {
					node = node->left;
					while (node->right)
						node = node->right;
				} else {
					while (node->parent && node->parent->left == node)
						node = node->parent;
					node = node->parent;
				}
				return node;
			}

			__declspec(property(get = getPrevious)) Node* Previous;
		};

		Node* root = nullptr;
		size_t size = 0;
		AllocatorType a;

		void rotateLeft(Node* node) {
			Node* right = node->right;
			Node* parent = node->parent;

			node->right = right->left;

			if (node->right)
				node->right->parent = node;

			right->parent = parent;

			if (!parent) {
				root = right;
			} else if (node == parent->left) {
				parent->left = right;
			} else {
				parent->right = right;
			}

			right->left = node;
			node->parent = right;
		}

		void rotateRight(Node* node) {
			Node* left = node->left;
			Node* parent = node->parent;

			node->left = left->right;

			if (node->left)
				node->left->parent = node;

			left->parent = parent;

			if (!parent) {
				root = left;
			} else if (node == parent->left) {
				parent->left = left;
			} else {
				parent->right = left;
			}

			left->right = node;
			node->parent = left;
		}

		inline Node* insertNode(const data_t& data) {
			if (!root) {
				void* mem = a.allocate(sizeof(Node));
				Node* node = new (mem)Node(data);
				root = node;
				root->color = NodeColor::BLACK;
				size = 1;
				return node;
			}

			Node* parent = root;
			Node* temp = root;
			while (temp) {
				parent = temp;
				auto ordering = traits.getKey(data) <=> traits.getKey(parent->data);
				if (ordering == 0) {
					parent->data = data;
					return parent;
				}
				if (ordering < 0) {
					temp = parent->left;
				} else {
					temp = parent->right;
				}
			}

			void* mem = a.allocate(sizeof(Node));
			Node* node = new (mem)Node(data);
			if (traits.getKey(data) < traits.getKey(parent->data)) {
				parent->left = node;
			} else {
				parent->right = node;
			}
			node->parent = parent;
			fixInsert(node);
			size++;
			return node;
		}

		void fixInsert(Node* node) {
			Node* parent = nullptr;
			Node* grandparent = nullptr;

			while (node != root && node->parent->color == NodeColor::RED) {
				parent = node->parent;
				grandparent = parent->parent;

				if (parent == grandparent->left) {
					Node* uncle = grandparent->right;

					if (uncle && uncle->color == NodeColor::RED) {
						grandparent->color = NodeColor::RED;
						parent->color = NodeColor::BLACK;
						uncle->color = NodeColor::BLACK;
						node = grandparent;
					} else {
						if (node == parent->right) {
							node = parent;
							rotateLeft(node);
							parent = node->parent;
							grandparent = parent->parent;
						}

						parent->color = NodeColor::BLACK;
						grandparent->color = NodeColor::RED;
						rotateRight(grandparent);
					}
				} else {
					Node* uncle = grandparent->left;

					if (uncle && (uncle->color == NodeColor::RED)) {
						grandparent->color = NodeColor::RED;
						parent->color = NodeColor::BLACK;
						uncle->color = NodeColor::BLACK;
						node = grandparent;
					} else {
						if (node == parent->left) {
							node = parent;
							rotateRight(node);
							parent = node->parent;
							grandparent = parent->parent;
						}

						parent->color = NodeColor::BLACK;
						grandparent->color = NodeColor::RED;
						rotateLeft(grandparent);
					}
				}
			}

			root->color = NodeColor::BLACK;
		}

		Node* findNodeToReplace(Node* node) {
			if (node->left && node->right) {
				Node* temp = node->left;
				while (temp->right)
					temp = temp->right;
				return temp;
			}

			if (!node->left && !node->right)
				return nullptr;

			if (node->left)
				return node->left;

			return node->right;
		}

		void deleteNode(Node* node) {
			Node* nodeToRemove = findNodeToReplace(node);
			if (nodeToRemove) {
				node->data = std::move(nodeToRemove->data);
				node = nodeToRemove;
			}

			if (!node->left && !node->right) {
				if (node == root) {
					root = nullptr;
				} else {
					fixDelete(node);

					Node* parent = node->parent;
					if (node->isOnLeft()) {
						parent->left = nullptr;
					} else {
						parent->right = nullptr;
					}
				}
				node->~Node();
				a.deallocate(node);
			} else {
				deleteNode(node);
			}
		}

		void fixDelete(Node* node) {
			while (node != root && node->color == NodeColor::BLACK) {
				Node* parent = node->parent;
				Node* sibling;
				if (node->isOnLeft()) {
					sibling = parent->right;
				} else {
					sibling = parent->left;
				}

				if (!sibling)
					return;

				if (sibling->color == NodeColor::BLACK) {
					if ((!sibling->left || sibling->left->color == NodeColor::BLACK) && (!sibling->right || sibling->right->color == NodeColor::BLACK)) {
						sibling->color = NodeColor::RED;
						if (parent->color == NodeColor::BLACK) {
							node = node->parent;
						} else {
							parent->color = NodeColor::BLACK;
							return;
						}
					} else if (!sibling->isOnLeft() && sibling->left && sibling->left->color == NodeColor::RED && (!sibling->right || sibling->right->color == NodeColor::BLACK)) {
						sibling->left->color = NodeColor::BLACK;
						sibling->color = NodeColor::RED;
						rotateRight(sibling);
					} else if (sibling->isOnLeft() && sibling->right && sibling->right->color == NodeColor::RED && (!sibling->left || sibling->left->color == NodeColor::BLACK)) {
						sibling->right->color = NodeColor::BLACK;
						sibling->color = NodeColor::RED;
						rotateLeft(sibling);
					}
					if (!sibling->isOnLeft() && sibling->right && sibling->right->color == NodeColor::RED) {
						std::swap(sibling->color, parent->color);
						rotateLeft(parent);
						sibling->right->color = NodeColor::BLACK;
						return;
					} else if (sibling->isOnLeft() && sibling->left && sibling->left->color == NodeColor::RED) {
						std::swap(sibling->color, parent->color);
						rotateRight(parent);
						sibling->left->color = NodeColor::BLACK;
						return;
					}
				} else if (sibling->color == NodeColor::RED) {
					sibling->color = NodeColor::BLACK;
					parent->color = NodeColor::RED;
					if (node->isOnLeft()) {
						rotateLeft(parent);
					} else {
						rotateRight(parent);
					}
				}
			}
		}

		inline Node* findNode(const key_t& key) const {
			Node* node = root;

			while (node) {
				auto ordering = key <=> traits.getKey(node->data);
				if (ordering < 0) {
					if (!node->left)
						break;
					node = node->left;
				} else if (ordering == 0) {
					return node;
				} else {
					if (!node->right)
						break;
					node = node->right;
				}
			}

			return nullptr;
		}

		inline void clear(Node* node) {
			if (!node)
				return;

			clear(node->left);
			clear(node->right);

			node->~Node();
			a.deallocate(node);
		}

#ifdef _DEBUG
		bool verifyRedBlack(Node* node) {
			if (!node)
				return true;

			if (node->color == NodeColor::RED) {
				return (!node->left || node->left->color == NodeColor::BLACK)
					&& (!node->right || node->right->color == NodeColor::BLACK)
					&& (node->parent->color == NodeColor::BLACK);
			}

			return verifyRedBlack(node->left) && verifyRedBlack(node->right);
		}

		uint32_t getBlackCount(Node* node, bool& correct) {
			if (!node || !correct)
				return 0;

			uint32_t blackCount = getBlackCount(node->left, correct);
			if (blackCount != getBlackCount(node->right, correct))
				correct = false;

			if (node->color == NodeColor::BLACK)
				blackCount++;
			return blackCount;
		}
#endif

	public:
		using iterator = TreeNodeIterator<data_t, Node>;
		using const_iterator = ConstTreeNodeIterator<data_t, Node>;
		using reverse_iterator = ReverseTreeNodeIterator<data_t, Node>;
		using const_reverse_iterator = ConstReverseTreeNodeIterator<data_t, Node>;

		Tree(AllocatorType a = AllocatorType()):a(a) {}

		Tree(const Tree& other) {
			for (auto& item : other)
				put(item);
		}

		Tree(const std::initializer_list<data_t>& list) {
			for (auto& item : list)
				put(item);
		}

		template<Iterable<data_t> CollectionType>
		Tree(const CollectionType& collection) {
			putAll(collection);
		}

		Tree(Tree&& other) {
			if (a != other.a)
				throw IncompatibleAllocatorsException("cannot move items between two allocators - copy instead");
			root = other.root;
			other.root = nullptr;
			size = other.size;
			other.size = 0;
		}

		~Tree() {
			clear();
		}

		inline size_t getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) size_t Size;

		inline bool isEmpty()const {
			return size == 0;
		}

		__declspec(property(get = isEmpty)) bool Empty;

		inline value_t& get(const key_t& key) {
			Node* node = findNode(key);
			if (!node)
				node = insertNode(traits.makeData(key));
			return node->data.value;
		}

		inline value_t& get(const key_t& key) const {
			Node* node = findNode(key);
			return node->data.value;
		}

		inline value_t& operator[](const key_t& key) {
			Node* node = findNode(key);
			if (!node)
				node = insertNode(traits.makeData(key));
			return node->data.value;
		}

		inline value_t& operator[](const key_t& key) const {
			Node* node = findNode(key);
			return node->data.value;
		}

		inline void put(const data_t& data) {
			insertNode(data);
		}

		template<typename... Args>
		inline void put(const key_t& key, Args&&... args) {
			insertNode(traits.makeData(key, std::forward<Args>(args)...));
		}

		template<Iterable<data_t> CollectionType>
		inline void putAll(const CollectionType& collection) {
			for (auto& item : collection)
				insertNode(item);
		}

		inline void putAll(const std::initializer_list<data_t>& list) {
			for (auto& item : list)
				insertNode(item);
		}

		inline void remove(const key_t& key) {
			Node* node = findNode(key);
			if (!node)
				return;

			deleteNode(node);
			size--;
		}

		inline iterator find(const key_t& key) {
			return iterator(findNode(key));
		}

		inline const_iterator find(const key_t& key) const {
			return const_iterator(findNode(key));
		}

		inline iterator begin() {
			Node* node = root;
			if (node) {
				while (node->left)
					node = node->left;
			}
			return iterator(node);
		}

		inline const_iterator begin() const {
			Node* node = root;
			if (node) {
				while (node->left)
					node = node->left;
			}
			return const_iterator(node);
		}

		inline iterator end() {
			return iterator();
		}

		inline const_iterator end() const {
			return const_iterator();
		}

		inline reverse_iterator rbegin() {
			Node* node = root;
			if (node) {
				while (node->right)
					node = node->right;
			}
			return reverse_iterator(node);
		}

		inline const_reverse_iterator rbegin() const {
			Node* node = root;
			if (node) {
				while (node->right)
					node = node->right;
			}
			return const_reverse_iterator(node);
		}

		inline reverse_iterator rend() {
			return reverse_iterator();
		}

		inline const_reverse_iterator rend() const {
			return const_reverse_iterator();
		}

		inline bool operator==(const Tree<TraitsType, AllocatorType>& other) const {
			if (this == &other)
				return true;
			if (size != other.size)
				return false;
			return std::equal(begin(), end(), other.begin());
		}

		inline bool operator!=(const Tree<TraitsType, AllocatorType>& other) const {
			return !(*this == other);
		}

		inline bool contains(const key_t& key) const {
			Node* node = root;

			while (node) {
				auto ordering = key <=> traits.getKey(node->data);
				if (ordering == 0)
					return true;
				if (ordering < 0) {
					node = node->left;
				} else {
					node = node->right;
				}
			}

			return false;
		}

		inline void clear() {
			clear(root);
			root = nullptr;
			size = 0;
		}

		Tree& operator=(const Tree& other) {
			if (this == &other)
				return *this;
			clear();
			for (const auto& item : other)
				put(data_t(item));
			return *this;
		}

		Tree& operator=(Tree&& other) {
			if (this == &other)
				return *this;
			if (a != other.a)
				throw IncompatibleAllocatorsException("cannot move items between two allocators - copy instead");
			clear();
			root = other.root;
			other.root = nullptr;
			size = other.size;
			other.size = 0;
			return *this;
		}

#ifdef _DEBUG
		inline bool verify() {
			bool correct = true;
			getBlackCount(root, correct);
			return correct && (!root || root->color == NodeColor::BLACK)
				&& verifyRedBlack(root);
		}
#endif
	};
}
