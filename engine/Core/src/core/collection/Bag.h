#pragma once

#include "ArrayCollection.h"

#include <cassert>

namespace Ghurund::Core {
    template<typename Value, typename AllocatorType = SimpleAllocator>
    class Bag:public ArrayCollection<Value, AllocatorType> {
    private:
        typedef ArrayCollection<Value, AllocatorType> A;

    public:
        using ArrayCollection<Value, AllocatorType>::ArrayCollection;

        Bag(const ArrayCollection<Value, AllocatorType>& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        Bag(const Bag& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        Bag(Bag&& t1):ArrayCollection<Value, AllocatorType>(std::move(t1)) {}

        inline Bag<Value, AllocatorType>& operator=(const Bag<Value, AllocatorType>& other) {
            if (this == &other)
                return *this;
            __super::operator=(other);
            return *this;
        }

        inline Bag<Value, AllocatorType>& operator=(Bag<Value, AllocatorType>&& other) {
            if (this == &other)
                return *this;
            __super::operator=(std::move(other));
            return *this;
        }

        inline void add(const Value& item) {
            if (A::size == A::capacity)
                A::resize((size_t)(A::capacity * 1.6));
            new(A::v + A::size) Value(item);
            A::size++;
        }

        inline void addAll(const ArrayCollection<Value>& list) {
            if (A::capacity < A::size + list.Size)
                A::resize(A::size + list.Size);
            auto it = list.begin();
            for (size_t i = 0; i < list.Size; i++, it++)
                new(A::v + A::size + i) Value(*it);
            A::size += list.Size;
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            if (A::capacity < A::size + list.size())
                A::resize(A::size + list.size());
            const Value* j = list.begin();
            for (size_t i = 0; i < list.size(); i++, j++)
                new(A::v + A::size + i) Value(*j);
            A::size += list.size();
        }

        inline Value& get(size_t i) const {
            _____________________check(i < A::size, "Index out of bounds.\n");
            return A::v[i];
        }

        inline Value& operator[](size_t i) const {
            _____________________check(i < A::size, "Index out of bounds.\n");
            return A::v[i];
        }

        inline void set(size_t i, const Value& item) {
            _____________________check(i < A::size, "Index out of bounds.\n");
            new(A::v + i) Value(item);
            A::v[i].~Value();
        }

        inline void set(size_t i, Value&& item) {
            _____________________check(i < A::size, "Index out of bounds.\n");
            new(A::v + i) Value(std::move(item));
            A::v[i].~Value();
        }

        inline size_t indexOf(const Value& item) const {
            for (size_t i = 0; i < A::size; i++)
                if (A::v[i] == item)
                    return i;
            return A::size;
        }

        inline void removeAt(size_t i) {
            _____________________check(i < A::size, "Index out of bounds.\n");
            A::v[i] = std::move(A::v[A::size - 1]);
            A::v[A::size - 1].~Value();
            A::size--;
        }

        inline void remove(const Value& item) {
            size_t i = 0;
            for (; i < A::size; i++) {
                if (A::v[i] == item)
                    break;
            }
            _____________________check(i < A::size, "Index out of bounds.\n");
            A::v[i] = std::move(A::v[A::size - 1]);
            A::v[A::size - 1].~Value();
            A::size--;
        }

        using A::operator==;
        using A::operator!=;
    };
}