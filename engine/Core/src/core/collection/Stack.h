#pragma once

#include "ArrayCollection.h"

namespace Ghurund::Core {
    template<typename Value, typename AllocatorType = SimpleAllocator>
    class Stack:public ArrayCollection<Value, AllocatorType> {
    private:
        typedef ArrayCollection<Value, AllocatorType> A;
    
    public:
        using ArrayCollection<Value, AllocatorType>::ArrayCollection;

        Stack(const ArrayCollection<Value, AllocatorType>& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        Stack(const Stack& t1):ArrayCollection<Value, AllocatorType>(t1) {}

        Stack(Stack&& t1):ArrayCollection<Value, AllocatorType>(std::move(t1)) {}

        inline Stack<Value, AllocatorType>& operator=(const Stack<Value, AllocatorType>& other) {
            __super::operator=(other);
            return *this;
        }

        inline Stack<Value, AllocatorType>& operator=(Stack<Value, AllocatorType>&& other) noexcept {
            __super::operator=(std::move(other));
            return *this;
        }

        inline Value& top() {
            return A::v[A::size - 1];
        }

        inline void push(const Value& item) {
            if (A::size == A::capacity)
                A::resize((size_t)(A::capacity * 1.6));
            new(A::v + A::size) Value(item);
            A::size++;
        }

        inline void pushAll(const ArrayCollection<Value>& list) {
            if (A::capacity < A::size + list.Size)
                A::resize(A::size + list.Size);
            const Value* j = list.begin();
            for (size_t i = 0; i < list.Size; i++, j++)
                new(A::v + A::size + i) Value(*j);
            A::size += list.Size;
        }

        inline void pushAll(const std::initializer_list<Value>& list) {
            if (A::capacity < A::size + list.size())
                A::resize(A::size + list.size());
            const Value* j = list.begin();
            for (size_t i = 0; i < list.size(); i++, j++)
                new(A::v + A::size + i) Value(*j);
            A::size += list.size();
        }

        inline Value pop() {
            Value item = A::v[A::size - 1];
            A::v[A::size - 1].~Value();
            A::size--;
            return item;
        }

        inline size_t indexOf(const Value& item) const {
            for (size_t i = 0; i < A::size; i++)
                if (A::v[i] == item)
                    return i;
            return A::size;
        }

        using A::operator==;
        using A::operator!=;
    };
}