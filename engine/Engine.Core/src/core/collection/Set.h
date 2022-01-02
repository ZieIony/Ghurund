#pragma once

#include "List.h"

#include <cassert>

namespace Ghurund::Core {
    /**
    * Doesn't guarantee order, cannot have duplicates
    */
    template<typename Value, typename AllocatorType = SimpleAllocator>
    class Set:public ArrayCollection<Value, AllocatorType> {
    private:
        typedef ArrayCollection<Value, AllocatorType> A;

    public:
        using ArrayCollection<Value, AllocatorType>::ArrayCollection;

        Set(const ArrayCollection<Value, AllocatorType>& collection) {
            addAll(collection);
        }

        Set(const Set& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        Set(Set&& t1):ArrayCollection<Value, AllocatorType>(std::move(t1)) {}

        Set(const std::initializer_list<Value>& list) {
            addAll(list);
        }

        inline Set<Value, AllocatorType>& operator=(const Set<Value, AllocatorType>& other) {
            __super::operator=(other);
            return *this;
        }

        inline Set<Value, AllocatorType>& operator=(Set<Value, AllocatorType>&& other) {
            __super::operator=(std::move(other));
            return *this;
        }

        inline void add(const Value& item) {
            if (A::contains(item))
                return;
            if (A::size == A::capacity)
                A::resize((size_t)(A::capacity * 1.6));
            new(A::v + A::size) Value(item);
            A::size++;
        }

        inline void addAll(const ArrayCollection<Value>& list) {
            for (const Value& item : list)
                add(item);
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            for (const Value& item : list)
                add(item);
        }

        inline void remove(const Value& item) {
            size_t i = 0;
            for (; i < A::size; i++) {
                if (A::v[i] == item)
                    break;
            }
            _ASSERT_EXPR(i < A::size, "Index out of bounds.\n");
            A::v[i] = std::move(A::v[A::size - 1]);
            A::v[A::size - 1].~Value();
            A::size--;
        }

        using A::operator==;
        using A::operator!=;
    };
}