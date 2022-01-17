#pragma once

#include "core/allocation/SimpleAllocator.h"
#include "core/collection/iterator/ListNodeIterator.h"
#include "core/collection/iterator/ReverseListNodeIterator.h"

#include <cassert>
#include <iterator>

namespace Ghurund::Core {
    template<typename Value, typename AllocatorType = SimpleAllocator>
    class LinkedList {
    private:
        template<typename Value>
        struct Node {
            Value data;
            Node<Value>* prev = nullptr;
            Node<Value>* next = nullptr;

            Node(const Value& data):data(data) {}
        };

        AllocatorType a;

        size_t size = 0;
        Node<Value>* first = nullptr;
        Node<Value>* last = nullptr;

    public:
        using iterator_t = ListNodeIterator<Value, Node<Value>>;
        using constIterator_t = ConstListNodeIterator<Value, Node<Value>>;
        using reverseIterator_t = ReverseListNodeIterator<Value, Node<Value>>;
        using constReverseIterator_t = ConstReverseListNodeIterator<Value, Node<Value>>;

        LinkedList(AllocatorType a = AllocatorType()):a(a) {}

        LinkedList(const LinkedList& other) : a(other.a) {
            for (const Value& item : other)
                add(item);
        }

        template<typename CollectionType>
        LinkedList(const CollectionType& other, AllocatorType a = AllocatorType()) : a(a) {
            for (const Value& item : other)
                add(item);
        }

        template<std::forward_iterator IteratorType>
        LinkedList(IteratorType& begin, IteratorType& end, AllocatorType a = AllocatorType()) : a(a) {
            for (IteratorType& iter = begin; iter < end; ++iter)
                add(*iter);
        }

        LinkedList(LinkedList<Value, AllocatorType>&& other) noexcept {
            a = std::move(other.a);
            size = other.size;
            other.size = 0;
            first = other.first;
            other.first = nullptr;
            last = other.last;
            other.last = nullptr;
        }

        LinkedList(const std::initializer_list<Value>& other, AllocatorType a = AllocatorType()):a(a) {
            for (const Value& item : other)
                add(item);
        }

        ~LinkedList() {
            clear();
        }

        template<typename CollectionType>
        LinkedList<Value, AllocatorType>& operator=(const CollectionType& other) {
            if (this == &other)
                return *this;
            clear();
            for (const Value& item : other)
                add(item);
            return *this;
        }

        LinkedList<Value, AllocatorType>& operator=(const LinkedList<Value, AllocatorType>& other) {
            if (this == &other)
                return *this;
            clear();
            for (const Value& item : other)
                add(item);
            return *this;
        }

        LinkedList<Value, AllocatorType>& operator=(LinkedList<Value, AllocatorType>&& other) noexcept {
            if (this == &other)
                return *this;
            size = other.size;
            other.size = 0;
            first = other.first;
            other.first = nullptr;
            last = other.last;
            other.last = nullptr;
            return *this;
        }

        inline size_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline bool isEmpty() const {
            return size == 0;
        }

        __declspec(property(get = isEmpty)) bool Empty;

        inline void add(const Value& item) {
            void* mem = a.allocate(sizeof(Node<Value>));
            Node<Value>* node = new (mem)Node<Value>(item);
            if (!first) {
                first = node;
                last = node;
            } else {
                last->next = node;
                node->prev = last;
                last = node;
            }
            size++;
        }

        template<std::forward_iterator IteratorType>
        inline void addAll(IteratorType begin, IteratorType end) {
            for (IteratorType& iter = begin; iter < end; ++iter)
                add(*iter);
        }

        template<typename CollectionType>
        inline void addAll(const CollectionType& list) {
            for (const Value& item : list)
                add(item);
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            for (const Value& item : list)
                add(item);
        }

        inline void insert(size_t i, const Value& item) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            void* mem = a.allocate(sizeof(Node<Value>));
            Node<Value>* node = new (mem)Node<Value>(item);
            Node<Value>* prev = nullptr;
            Node<Value>* next = first;
            for (size_t j = 0; j < i; j++) {
                prev = next;
                next = next->next;
            }
            if (prev) {
                prev->next = node;
            } else {
                first = node;
            }
            if (next) {
                next->prev = node;
            } else {
                last = node;
            }
            node->prev = prev;
            node->next = next;
            size++;
        }

        inline Value& get(size_t i) const {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            Node<Value>* temp = first;
            for (size_t j = 0; j < i; j++)
                temp = temp->next;
            return temp->data;
        }

        inline Value& operator[](size_t i) const {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            Node<Value>* temp = first;
            for (size_t j = 0; j < i; j++)
                temp = temp->next;
            return temp->data;
        }

        inline void set(size_t i, const Value& item) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            Node<Value>* temp = first;
            for (size_t j = 0; j < i; j++)
                temp = temp->next;
            temp->data = item;
        }

        inline size_t indexOf(const Value& item) const {
            Node<Value>* temp = first;
            for (size_t i = 0; i < size; i++) {
                if (temp->data == item)
                    return i;
                temp = temp->next;
            }
            return size;
        }

        inline void removeAt(size_t i) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            Node<Value>* node = first;
            for (size_t j = 0; j < i; j++)
                node = node->next;
            if (node == first)
                first = node->next;
            if (node == last)
                last = node->prev;
            if (node->next)
                node->next->prev = node->prev;
            if (node->prev)
                node->prev->next = node->next;
            node->~Node<Value>();
            a.deallocate(node);
            size--;
        }

        inline void remove(const Value& item) {
            Node<Value>* node = first;
            for (size_t j = 0; j < size; j++) {
                if (node->data == item)
                    break;
                node = node->next;
            }
            if (node == first)
                first = node->next;
            if (node == last)
                last = node->prev;
            if (node->next)
                node->next->prev = node->prev;
            if (node->prev)
                node->prev->next = node->next;
            node->~Node<Value>();
            a.deallocate(node);
            size--;
        }

        inline Value& front() const {
            return first->data;
        }

        inline Value& back() const {
            return last->data;
        }

        inline void removeFront() {
            Node<Value>* node = first;
            first = node->next;
            if (node->next)
                node->next->prev = node->prev;
            node->~Node<Value>();
            a.deallocate(node);
            size--;
        }

        inline void removeBack() {
            Node<Value>* node = last;
            last = node->prev;
            if (node->prev)
                node->prev->next = node->next;
            node->~Node<Value>();
            a.deallocate(node);
            size--;
        }

        // TODO: reduce iteration
        inline void removeAll(const std::initializer_list<Value>& list) {
            for (const Value& item : list)
                remove(item);
        }

        inline void clear() {
            while (first) {
                Node<Value>* temp = first;
                first = first->next;
                a.deallocate(temp);
            }
            size = 0;
        }

        inline iterator_t begin() {
            return iterator_t(first);
        }

        inline constIterator_t begin() const {
            return constIterator_t(first);
        }

        inline iterator_t end() {
            return iterator_t();
        }

        inline constIterator_t end() const {
            return constIterator_t();
        }

        inline reverseIterator_t rbegin() {
            return reverseIterator_t(last);
        }

        inline constReverseIterator_t rbegin() const {
            return constReverseIterator_t(last);
        }

        inline reverseIterator_t rend() {
            return reverseIterator_t();
        }

        inline constReverseIterator_t rend() const {
            return constReverseIterator_t();
        }

        inline bool operator==(const LinkedList<Value, AllocatorType>& other) const {
            if (this == &other)
                return true;
            if (size != other.size)
                return false;
            for (auto iter = begin(), iter2 = other.begin(); iter != end(), iter2 != other.end(); ++iter, ++iter2) {
                if (*iter != *iter2)
                    return false;
            }
            return true;
        }

        inline bool operator!=(const LinkedList<Value, AllocatorType>& other) const {
            return !(*this == other);
        }

        inline bool contains(const Value& item) const {
            for (auto& i : *this)
                if (i == item)
                    return true;
            return false;
        }

        inline void deleteItems() {
            while (first) {
                delete first->data;
                Node<Value>* temp = first;
                first = first->next;
                a.deallocate(temp);
            }
            size = 0;
        }
    };

}