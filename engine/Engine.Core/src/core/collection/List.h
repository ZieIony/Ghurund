#pragma once

#include "ArrayCollection.h"
#include "Array.h"

#include <cassert>

namespace Ghurund::Core {
    template<typename Value, typename AllocatorType = SimpleAllocator>
    class List:public ArrayCollection<Value, AllocatorType> {
    private:
        typedef ArrayCollection<Value, AllocatorType> A;

    public:
        using ArrayCollection<Value, AllocatorType>::ArrayCollection;

        List(const ArrayCollection<Value, AllocatorType>& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        List(const List& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        List(List&& t1):ArrayCollection<Value, AllocatorType>(std::move(t1)) {}

        List<Value, AllocatorType>& operator=(const List<Value, AllocatorType>& other) {
            __super::operator=(other);
            return *this;
        }

        List<Value, AllocatorType>& operator=(List<Value, AllocatorType>&& other) noexcept {
            __super::operator=(std::move(other));
            return *this;
        }

        inline void add(const Value& item) {
            if (A::size == A::capacity)
                A::resize((size_t)(A::capacity * 1.6));
            new(A::v + A::size) Value(item);
            A::size++;
        }

        inline void addAll(const Array<Value>& array) {
            if (A::capacity < A::size + array.Size)
                A::resize(A::size + array.Size);
            auto it = array.begin();
            for (size_t i = 0; i < array.Size; i++, it++)
                new(A::v + A::size + i) Value(*it);
            A::size += array.Size;
        }

        inline void addAll(const ArrayCollection<Value>& collection) {
            if (A::capacity < A::size + collection.Size)
                A::resize(A::size + collection.Size);
            auto it = collection.begin();
            for (size_t i = 0; i < collection.Size; i++, it++)
                new(A::v + A::size + i) Value(*it);
            A::size += collection.Size;
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            if (A::capacity < A::size + list.size())
                A::resize(A::size + list.size());
            const Value* j = list.begin();
            for (size_t i = 0; i < list.size(); i++, j++)
                new(A::v + A::size + i) Value(*j);
            A::size += list.size();
        }

        inline void insert(size_t i, const Value& item) {
            _ASSERT_EXPR(i <= A::size, "Index out of bounds.\n");
            if (A::size == A::capacity)
                A::resize((size_t)(A::capacity * 1.6));
            if (i < A::size) {
                new(A::v + A::size) Value(A::v[A::size - 1]);
                for (size_t j = A::size - 1; j > i; j--)
                    A::v[j] = std::move(A::v[j - 1]);
                A::v[i].~Value();
            }
            new(A::v + i) Value(item);
            A::size++;
        }

        inline Value& get(size_t i) const {
            _ASSERT_EXPR(i < A::size, "Index out of bounds.\n");
            return A::v[i];
        }

        inline Value& operator[](size_t i) const {
            _ASSERT_EXPR(i < A::size, "Index out of bounds.\n");
            return A::v[i];
        }

        inline void set(size_t i, const Value& item) {
            _ASSERT_EXPR(i < A::size, "Index out of bounds.\n");
            new(A::v + i) Value(item);
            A::v[i].~Value();
        }

        inline size_t indexOf(const Value& item) const {
            for (size_t i = 0; i < A::size; i++)
                if (A::v[i] == item)
                    return i;
            return A::size;
        }

        inline void removeAt(size_t i) {
            _ASSERT_EXPR(i < A::size, "Index out of bounds.\n");
            for (size_t j = i; j < A::size - 1; j++)
                A::v[j] = std::move(A::v[j + 1]);
            A::v[A::size - 1].~Value();
            A::size--;
        }

        inline void remove(const Value& item) {
            size_t i = indexOf(item);
            _ASSERT_EXPR(i < A::size, "Index out of bounds.\n");
            for (size_t j = i; j < A::size - 1; j++)
                A::v[j] = std::move(A::v[j + 1]);
            A::v[A::size - 1].~Value();
            A::size--;
        }

        inline void removeAll(const std::initializer_list<Value>& list) {
            size_t i = 0, j = 0, k;
            const Value* iterator = list.begin();
            for (; iterator != list.end(); i = 0, j = 0) {
                for (; i < A::size + i - j;) {
                    if (j > i)
                        A::v[i] = std::move(A::v[j]);
                    if (A::v[i] == *iterator) {
                        iterator++;
                    } else {
                        i++;
                    }
                    j++;
                }
                if (j != i) {
                    k = j - i;
                    for (; i < A::size; i++)
                        A::v[i].~Value();
                    A::size -= k;
                } else {
                    iterator++;
                }
            }
        }

        using A::operator==;
        using A::operator!=;
    };

}