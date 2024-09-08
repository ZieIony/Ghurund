#pragma once

#include "LinkedList.h"
#include "core/concepts/Iterable.h"

namespace Ghurund::Core {
    template<typename Value, typename AllocatorType = SimpleAllocator>
    class Queue {
    private:
        LinkedList<Value, AllocatorType> list;

    public:
        Queue(AllocatorType a = AllocatorType()):list(a) {}

        Queue(const Queue& other): list(other.list) {}

        template<Iterable CollectionType>
        Queue(const CollectionType& other) : list(other) {}

        Queue(Queue<Value, AllocatorType>&& other) noexcept:list(std::move(other.list)) {}

        Queue(const std::initializer_list<Value>& other, AllocatorType a = AllocatorType()):list(other, a) {}

        ~Queue() {}

        template<Iterable Collection>
        Queue<Value, AllocatorType>& operator=(const Collection& other) {
            if (this == &other)
                return *this;
            clear();
            for (const Value& item : other)
                add(item);
            return *this;
        }

        Queue<Value, AllocatorType>& operator=(const Queue<Value, AllocatorType>& other) {
            if (this == &other)
                return *this;
            list = other.list;
            return *this;
        }

        Queue<Value, AllocatorType>& operator=(Queue<Value, AllocatorType>&& other) noexcept {
            if (this == &other)
                return *this;
            list = std::move(other.list);
            return *this;
        }

        inline size_t getSize() const {
            return list.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        inline bool isEmpty() const {
            return list.isEmpty();
        }

        __declspec(property(get = isEmpty)) bool Empty;

        inline void add(const Value& item) {
            list.add(item);
        }

        template<std::forward_iterator IteratorType>
        inline void addAll(IteratorType begin, IteratorType end) {
            list.addAll(begin, end);
        }

        template<typename CollectionType>
        inline void addAll(const CollectionType& list) {
            this->list.addAll(list);
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            this->list.addAll(list);
        }

        inline Value& get(size_t i) const {
            return list.get(i);
        }

        inline Value& operator[](size_t i) const {
            return list[i];
        }

        inline size_t indexOf(const Value& item) const {
            return list.indexOf(item);
        }

        inline void clear() {
            list.clear();
        }

        inline LinkedList<Value, AllocatorType>::iterator_t begin() {
            return list.begin();
        }

        inline LinkedList<Value, AllocatorType>::const_iterator begin() const {
            return list.begin();
        }

        inline LinkedList<Value, AllocatorType>::iterator_t end() {
            return list.end();
        }

        inline LinkedList<Value, AllocatorType>::const_iterator end() const {
            return list.end();
        }

        inline LinkedList<Value, AllocatorType>::reverse_iterator rbegin() {
            return list.rbegin();
        }

        inline LinkedList<Value, AllocatorType>::const_reverse_iterator rbegin() const {
            return list.rbegin();
        }

        inline LinkedList<Value, AllocatorType>::reverse_iterator rend() {
            return list.rend();
        }

        inline LinkedList<Value, AllocatorType>::const_reverse_iterator rend() const {
            return list.rend();
        }

        inline bool operator==(const Queue<Value, AllocatorType>& other) const {
            return list == other.list;
        }

        inline bool operator!=(const Queue<Value, AllocatorType>& other) const {
            return list != other.list;
        }

        inline bool contains(const Value& item) const {
            return list.contains(item);
        }

        inline void deleteItems() {
            list.deleteItems();
        }

        inline Value& front() const {
            return list.front();
        }

        inline Value& back() const {
            return list.back();
        }

        inline void remove() {
            list.removeFront();
        }
    };
}