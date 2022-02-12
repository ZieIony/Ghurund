#pragma once

#include "iterator/ArrayIterator.h"
#include "iterator/ReverseArrayIterator.h"
#include "CollectionWithCapacity.h"
#include "core/allocation/SimpleAllocator.h"

namespace Ghurund::Core {
    template<typename Value, typename AllocatorType = SimpleAllocator>
    class ArrayCollection:public CollectionWithCapacity {
    protected:
        Value* v;
        AllocatorType a;

    public:
        ArrayCollection(AllocatorType a = AllocatorType()):a(a) {
            v = (Value*)a.allocate(sizeof(Value) * capacity);
        }

        ArrayCollection(size_t capacity, AllocatorType a = AllocatorType()):CollectionWithCapacity(capacity), a(a) {
            v = (Value*)a.allocate(sizeof(Value) * capacity);
        }

        ArrayCollection(const ArrayCollection& t1):CollectionWithCapacity(t1) {
            v = (Value*)a.allocate(sizeof(Value) * capacity);
            for (size_t i = 0; i < size; i++)
                new (v + i)Value(t1.v[i]);
        }

        ArrayCollection(ArrayCollection&& other):CollectionWithCapacity(std::move(other)) {
            if (a != other.a)
                throw IncompatibleAllocatorsException("cannot move items between two allocators - copy instead");
            v = other.v;
            other.v = nullptr;
        }

        ArrayCollection(const std::initializer_list<Value>& list) {
            size = initial = capacity = list.size();
            v = (Value*)a.allocate(sizeof(Value) * capacity);
            int i = 0;
            for (auto it = list.begin(); it != list.end(); ++it, i++)
                new (v + i)Value(*it);
        }

        ~ArrayCollection() = 0 {
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            a.deallocate(v);
        }

        inline void resize(size_t c) {
            capacity = c;
            Value* other = (Value*)a.allocate(sizeof(Value) * capacity);
            if (c >= size) {
                for (size_t i = 0; i < size; i++) {
                    new (other + i) Value(v[i]);
                    v[i].~Value();
                }
            } else {
                for (size_t i = 0; i < c; i++) {
                    new (other + i) Value(v[i]);
                    v[i].~Value();
                }
                for (size_t i = c; i < size; i++)
                    v[i].~Value();
                size = c;
            }
            a.deallocate(v);
            v = other;
        }

        inline void clear() {
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            __super::clear();
        }

        inline ArrayIterator<Value> begin() {
            return ArrayIterator<Value>(v);
        }

        inline ConstArrayIterator<Value> begin() const {
            return ConstArrayIterator<Value>(v);
        }

        inline ArrayIterator<Value> end() {
            return ArrayIterator<Value>(v + size);
        }

        inline ConstArrayIterator<Value> end() const {
            return ConstArrayIterator<Value>(v + size);
        }

        inline ReverseArrayIterator<Value> rbegin() {
            return ReverseArrayIterator<Value>(v + size - 1);
        }

        inline ConstReverseArrayIterator<Value> rbegin() const {
            return ConstReverseArrayIterator<Value>(v + size - 1);
        }

        inline ReverseArrayIterator<Value> rend() {
            return ReverseArrayIterator<Value>(v - 1);
        }

        inline ConstReverseArrayIterator<Value> rend() const {
            return ConstReverseArrayIterator<Value>(v - 1);
        }

        inline bool contains(const Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return true;
            return false;
        }

        inline void deleteItems() {
            for (size_t i = 0; i < size; i++) {
                delete v[i];
                v[i].~Value();
            }
            size = 0;
        }

        inline bool operator==(const ArrayCollection<Value, AllocatorType>& other) const {
            if (__super::operator!=(other))
                return false;
            for (size_t i = 0; i < size; i++)
                if (v[i] != other.v[i])
                    return false;
            return true;
        }

        inline bool operator!=(const ArrayCollection<Value, AllocatorType>& other) const {
            return !(*this == other);
        }

        inline ArrayCollection<Value, AllocatorType>& operator=(const ArrayCollection<Value, AllocatorType>& other) {
            if (this == &other)
                return *this;
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            if (capacity != other.capacity) {
                a.deallocate(v);
                v = (Value*)a.allocate(sizeof(Value) * other.capacity);
            }
            __super::operator=(other);
            for (size_t i = 0; i < size; i++)
                new (v + i) Value(other.v[i]);
            return *this;
        }

        inline ArrayCollection<Value, AllocatorType>& operator=(ArrayCollection<Value, AllocatorType>&& other) {
            if (this == &other)
                return *this;
            if (a != other.a)
                throw IncompatibleAllocatorsException("cannot move items between two allocators - copy instead");
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            a.deallocate(v);
            __super::operator=(std::move(other));
            v = other.v;
            other.v = nullptr;
            return *this;
        }

        template<typename Predicate>
        inline size_t find(Predicate predicate) const {
            size_t i = 0;
            for (const Value& item : *this) {
                if (predicate(item))
                    return i;
                i++;
            }
            return size;
        }
    };
}