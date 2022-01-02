#pragma once

#include "List.h"

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
            __super::operator=(other);
            return *this;
        }

        inline Bag<Value, AllocatorType>& operator=(Bag<Value, AllocatorType>&& other) noexcept {
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
            const Value* j = list.begin();
            for (size_t i = 0; i < list.Size; i++, j++)
                new(A::v + A::size + i) Value(*j);
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