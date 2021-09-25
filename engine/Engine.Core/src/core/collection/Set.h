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

        Set(const ArrayCollection<Value, AllocatorType>& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        Set(const Set& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        Set(Set&& t1) noexcept:ArrayCollection<Value, AllocatorType>(std::move(t1)) {}

        Set(const std::initializer_list<Value> list) {
            Set<Value, AllocatorType> copy(list.size());
            for (const Value& item : list) {
                if (!A::contains(item))
                    copy.add(item);
            }
            A::size = A::initial = A::capacity = copy.Size;
            A::v = (Value*)A::a.allocate(sizeof(Value) * copy.Size);
            const Value* j = copy.begin();
            for (size_t i = 0; i < copy.Size; i++, j++)
                new(A::v + i) Value(*j);
        }

        Set<Value, AllocatorType>& operator=(const Set<Value, AllocatorType>& other) {
            if (this == &other)
                return *this;
            for (size_t i = 0; i < A::size; i++)
                A::v[i].~Value();
            if (A::capacity != other.capacity) {
                A::a.deallocate(A::v);
                A::v = (Value*)A::a.allocate(sizeof(Value) * other.capacity);
            }
            A::size = other.size;
            A::initial = other.initial;
            A::capacity = other.capacity;
            const Value* j = other.begin();
            for (size_t i = 0; i < A::size; i++, j++)
                new (A::v + i) Value(*j);
            return *this;
        }

        Set<Value, AllocatorType>& operator=(Set<Value, AllocatorType>&& other) noexcept {
            if (this == &other)
                return *this;
            A::size = other.size;
            other.size = 0;
            A::initial = other.initial;
            other.initial = 0;
            A::capacity = other.capacity;
            other.capacity = 0;
            A::v = other.v;
            other.v = nullptr;
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
            Set<Value, AllocatorType> copy(list.Size);
            for (const Value& item : list) {
                if (!A::contains(item))
                    copy.add(item);
            }
            if (A::capacity < A::size + copy.Size)
                A::resize(A::size + copy.Size);
            const Value* j = copy.begin();
            for (size_t i = 0; i < copy.Size; i++, j++)
                new(A::v + A::size + i) Value(*j);
            A::size += copy.Size;
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            Set<Value, AllocatorType> copy(list.size());
            for (const Value& item : list) {
                if (!A::contains(item))
                    copy.add(item);
            }
            if (A::capacity < A::size + copy.Size)
                A::resize(A::size + copy.Size);
            const Value* j = copy.begin();
            for (size_t i = 0; i < copy.Size; i++, j++)
                new(A::v + A::size + i) Value(*j);
            A::size += copy.Size;
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