#pragma once

#include "Common.h"
#include "Collection.h"
#include "core/allocation/SimpleAllocator.h"

namespace Ghurund::Core {
    template<typename Value, typename AllocatorType = SimpleAllocator>
    class Tree {
    private:
        enum class NodeColor:uint8_t {
            RED, BLACK
        };

        template<typename Value>
        struct Node {
            Value data;
            NodeColor color = NodeColor::RED;
            Node<Value>* left = nullptr;
            Node<Value>* right = nullptr;
            Node<Value>* parent = nullptr;

            Node(const Value& data):data(data) {}

            inline bool isOnLeft() { return this == parent->left; }
        };

        template<typename Value>
        class Iterator {
        private:
            Node<Value>* node;

        public:
            Iterator(Node<Value>* node):node(node) {}

            inline bool operator==(const Iterator<Value>& other) const {
                return node == other.node;
            }

            inline bool operator!=(const Iterator<Value>& other) const {
                return !this->operator==(other);
            }

            inline Iterator& operator=(Node<Value>* node) {
                this->node = node;
                return *this;
            }

            inline Iterator& operator++() {
                if (node->right) {
                    node = node->right;
                    while (node->left)
                        node = node->left;
                } else {
                    while (node->parent && node->parent->right == node)
                        node = node->parent;
                    node = node->parent;
                }
                return *this;
            }

            inline Iterator operator++(int) {
                return ++Iterator(node);
            }

            inline Iterator& operator--() {
                if (node->left) {
                    node = node->left;
                    while (node->right)
                        node = node->right;
                } else {
                    while (node->parent && node->parent->left == node)
                        node = node->parent;
                    node = node->parent;
                }
                return *this;
            }

            inline Iterator operator--(int) {
                return --Iterator(node);
            }

            inline Value& operator*() {
                return node->data;
            }
        };

        template<typename Value>
        class ConstIterator {
        private:
            Node<Value>* node;

        public:
            ConstIterator(Node<Value>* node):node(node) {}

            inline bool operator==(const ConstIterator<Value>& other) const {
                return node == other.node;
            }

            inline bool operator!=(const ConstIterator<Value>& other) const {
                return !this->operator==(other);
            }

            inline ConstIterator& operator=(Node<Value>* node) {
                this->node = node;
                return *this;
            }

            inline ConstIterator& operator++() {
                if (node->right) {
                    node = node->right;
                    while (node->left)
                        node = node->left;
                } else {
                    while (node->parent && node->parent->right == node)
                        node = node->parent;
                    node = node->parent;
                }
                return *this;
            }

            inline ConstIterator operator++(int) {
                return ++ConstIterator(node);
            }

            inline ConstIterator& operator--() {
                if (node->left) {
                    node = node->left;
                    while (node->right)
                        node = node->right;
                } else {
                    while (node->parent && node->parent->left == node)
                        node = node->parent;
                    node = node->parent;
                }
                return *this;
            }

            inline ConstIterator operator--(int) {
                return --ConstIterator(node);
            }

            inline const Value& operator*() {
                return node->data;
            }
        };

        Node<Value>* root = nullptr;
        size_t size = 0;
        AllocatorType a;

        void rotateLeft(Node<Value>* node) {
            Node<Value>* right = node->right;
            Node<Value>* parent = node->parent;

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

        void rotateRight(Node<Value>* node) {
            Node<Value>* left = node->left;
            Node<Value>* parent = node->parent;

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

        Node<Value>* insertNode(const Value& item) {
            if (!root) {
                void* mem = a.allocate(sizeof(Node<Value>));
                Node<Value>* node = new (mem)Node<Value>(item);
                root = node;
                return node;
            }

            Node<Value>* parent = root;
            Node<Value>* temp = root;
            while (temp) {
                parent = temp;
                if (item == parent->data)
                    return nullptr;
                if (item < parent->data) {
                    temp = parent->left;
                } else {
                    temp = parent->right;
                }
            }

            void* mem = a.allocate(sizeof(Node<Value>));
            Node<Value>* node = new (mem)Node<Value>(item);
            if (item < parent->data) {
                parent->left = node;
            } else {
                parent->right = node;
            }
            node->parent = parent;
            return node;
        }

        void fixInsert(Node<Value>* node) {
            Node<Value>* parent = nullptr;
            Node<Value>* grandparent = nullptr;

            while (node != root && node->parent->color == NodeColor::RED) {
                parent = node->parent;
                grandparent = parent->parent;

                if (parent == grandparent->left) {
                    Node<Value>* uncle = grandparent->right;

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
                    Node<Value>* uncle = grandparent->left;

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

        Node<Value>* findNodeToReplace(Node<Value>* node) {
            if (node->left && node->right) {
                Node<Value>* temp = node->left;
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

        void deleteNode(Node<Value>* node) {
            Node<Value>* nodeToRemove = findNodeToReplace(node);
            if (nodeToRemove) {
                node->data = std::move(nodeToRemove->data);
                node = nodeToRemove;
            }

            if (!node->left && !node->right) {
                if (node == root) {
                    root = nullptr;
                } else {
                    fixDelete(node);

                    Node<Value>* parent = node->parent;
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

        void fixDelete(Node<Value>* node) {
            while (node != root && node->color == NodeColor::BLACK) {
                Node<Value>* parent = node->parent;
                Node<Value>* sibling;
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

        Node<Value>* findNode(const Value& item) {
            Node<Value>* node = root;

            while (node) {
                if (item < node->data) {
                    if (!node->left)
                        break;
                    node = node->left;
                } else if (item == node->data) {
                    return node;
                } else {
                    if (!node->right)
                        break;
                    node = node->right;
                }
            }

            return nullptr;
        }

        void clear(Node<Value>* node) {
            if (!node)
                return;

            clear(node->left);
            clear(node->right);

            node->~Node();
            a.deallocate(node);
        }

        void deleteItems(Node<Value>* node) {
            if (!node)
                return;

            clear(node->left);
            clear(node->right);

            delete node->data;
            node->~Node();
            a.deallocate(node);
        }

#ifdef _DEBUG
        bool verifyRedBlack(Node<Value>* node) {
            if (!node)
                return true;

            if (node->color == NodeColor::RED) {
                return (!node->left || node->left->color == NodeColor::BLACK)
                    && (!node->right || node->right->color == NodeColor::BLACK)
                    && (node->parent->color == NodeColor::BLACK);
            }

            return verifyRedBlack(node->left) && verifyRedBlack(node->right);
        }

        uint32_t getBlackCount(Node<Value>* node, bool& correct) {
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
        Tree(AllocatorType a = AllocatorType()) {}

        Tree(const Tree& other) {
            for (const Value& item : other)
                add(item);
        }

        Tree(const std::initializer_list<Value>& list) {
            for (const Value& item : list)
                add(item);
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

        inline void add(const Value& item) {
            Node<Value>* node = insertNode(item);
            if (node) {
                fixInsert(node);
                size++;
            }
        }

        template<typename Collection>
        inline void addAll(const Collection& list) {
            for (Value& item : list)
                add(item);
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            for (const Value& item : list)
                add(item);
        }

        inline void remove(const Value& item) {
            Node<Value>* node = findNode(item);
            if (!node)
                return;

            deleteNode(node);
            size--;
        }

        template<typename Collection>
        inline void removeAll(const Collection& list) {
            for (Value& item : list)
                remove(item);
        }

        inline void removeAll(const std::initializer_list<Value>& list) {
            for (const Value& item : list)
                remove(item);
        }

        inline Iterator<Value> begin() {
            Node<Value>* node = root;
            if (node) {
                while (node->left)
                    node = node->left;
            }
            return Iterator<Value>(node);
        }

        inline ConstIterator<Value> begin() const {
            Node<Value>* node = root;
            if (node) {
                while (node->left)
                    node = node->left;
            }
            return ConstIterator<Value>(node);
        }

        inline Iterator<Value> end() {
            return Iterator<Value>(nullptr);
        }

        inline ConstIterator<Value> end() const {
            return ConstIterator<Value>(nullptr);
        }

        inline Iterator<Value> rbegin() {
            Node<Value>* node = root;
            if (node) {
                while (node->right)
                    node = node->right;
            }
            return Iterator<Value>(node);
        }

        inline ConstIterator<Value> rbegin() const {
            Node<Value>* node = root;
            if (node) {
                while (node->right)
                    node = node->right;
            }
            return ConstIterator<Value>(node);
        }

        inline Iterator<Value> rend() {
            return Iterator<Value>(nullptr);
        }

        inline ConstIterator<Value> rend() const {
            return ConstIterator<Value>(nullptr);
        }

        inline bool operator==(const Tree<Value, AllocatorType>& other) const {
            if (this == &other)
                return true;
            if (size != other.size)
                return false;
            for (ConstIterator<Value> iter = begin(), iter2 = other.begin(); iter != end(), iter2 != other.end(); ++iter, ++iter2) {
                if (*iter != *iter2)
                    return false;
            }
            return true;
        }

        inline bool operator!=(const Tree<Value, AllocatorType>& other) const {
            return !(*this == other);
        }

        inline bool contains(const Value& item) const {
            Node<Value>* node = root;

            while (node) {
                if (node->data == item)
                    return true;
                if (item < node->data) {
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
            for (const Value& item : other)
                add(item);
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

        inline void deleteItems() {
            deleteItems(root);
            root = nullptr;
            size = 0;
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
