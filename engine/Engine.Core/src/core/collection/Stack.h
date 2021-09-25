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

        Stack(Stack&& t1) noexcept:ArrayCollection<Value, AllocatorType>(std::move(t1)) {}

        Stack<Value, AllocatorType>& operator=(const Stack<Value, AllocatorType>& other) {
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

        Stack<Value, AllocatorType>& operator=(Stack<Value, AllocatorType>&& other) noexcept {
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