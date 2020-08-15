#pragma once

#include "Collection.h"

#include <functional>
#include <cassert>

namespace Ghurund {
    template<class Value> class List:public Collection {
    protected:
        Value* v;

#ifdef GHURUND_EDITOR
        std::function<void()> onItemAdded, onItemRemoved, onItemChanged;
#endif

        static const std::function<int(const void*, const void*)> DEFAULT_COMPARISON_FUNCTION;

    public:
        List() {
			v = (Value*)ghnew char[sizeof(Value) * capacity];
		}

        List(size_t initial) {
			this->initial = capacity = initial;
            v = (Value*)ghnew char[sizeof(Value) * capacity];
		}

        List(const List& t1) {
			capacity = t1.capacity;
            initial = t1.initial;
            size = t1.size;
            v = (Value*)ghnew char[sizeof(Value) * capacity];
            for (size_t i = 0; i < size; i++)
                new (v + i)Value(t1[i]);
		}

        List(const std::initializer_list<Value> list) {
			size = initial = capacity = list.size();
            v = (Value*)ghnew char[sizeof(Value) * capacity];
            int i = 0;
            for (auto it = list.begin(); it != list.end(); ++it, i++)
                new (v + i)Value(*it);
		}

        ~List() {
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            delete[](char*)v;
        }

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline size_t getCapacity()const {
            return capacity;
        }

        inline void resize(size_t c) {//if c<size some items will be lost, cannot resize to less than 1 item
            size_t c2 = std::max<size_t>(c, 1);
            Value* t1 = (Value*)ghnew char[sizeof(Value) * c2];
            capacity = c2;
            size = std::min(size, c);
            for (size_t i = 0; i < size; i++) {
                new (t1 + i) Value(v[i]);
                v[i].~Value();
            }
            delete[](char*)v;
            v = t1;
        }

        inline void add(const Value& e) {//allows to add null item
            if (size == capacity)
                resize((size_t)(capacity * 1.6));
			new(v + size) Value(e);
            size++;
#ifdef GHURUND_EDITOR
            if (onItemAdded != nullptr)
                onItemAdded();
#endif
        }

        inline void addAll(const List<Value>& list) {
            if (capacity < size + list.Size)
                resize(size + list.Size);
            for (size_t i = 0; i < list.Size; i++)
                new(v + size + i) Value(list[i]);
            size += list.Size;
#ifdef GHURUND_EDITOR
            if (onItemAdded != nullptr)
                onItemAdded();
#endif
        }

        inline void insert(size_t i, const Value& item) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            if (size == capacity)
                resize(capacity + initial);
            v[size] = v[i];
            v[i].~Value();
            new(v + i) Value(item);
            size++;
        }

        inline void insertKeepOrder(size_t i, const Value& item) {
            if (size == capacity)
                resize((size_t)(capacity * 1.6));
            if (i < size) {
                v[size] = v[size - 1];
                for (size_t j = size - 1; j > i; j--)
                    v[j] = std::move(v[j - 1]);
            }
            v[i].~Value();
            new(v + i) Value(item);
            size++;
        }

        inline void set(size_t i, const Value& e) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            v[i].~Value();
            new(v + i) Value(e);
        }

        inline Value& get(size_t i)const {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            return v[i];
        }

        inline void removeAt(size_t i) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            v[i] = std::move(v[size - 1]);
            v[size - 1].~Value();
            size--;
        }

        inline void removeAtKeepOrder(size_t i) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            if (i != size - 1) {
                for (size_t j = i; j < size - 1; j++)
                    v[j] = std::move(v[j + 1]);
            }
            v[size - 1].~Value();
            size--;
        }

        inline void remove(const Value& item) {
            size_t i = indexOf(item);
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            v[i] = std::move(v[size - 1]);
            v[size - 1].~Value();
            size--;
        }

        inline void removeKeepOrder(const Value& item) {
            size_t i = indexOf(item);
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            if (i != size - 1) {
                for (size_t j = i; j < size - 1; j++)
                    v[j] = std::move(v[j + 1]);
            }
            v[size - 1].~Value();
            size--;
        }

        inline Value* begin() {
            return v;
        }

        inline Value* begin() const {
            return v;
        }

        inline Value* end() {
            return v + size;
        }

        inline Value* end() const {
            return v + size;
        }

        inline size_t indexOf(const Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return i;
            return size;
        }

        inline bool contains(const Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return true;
            return false;
        }

        inline Value& operator[](size_t i)const {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            return v[i];
        }

        List<Value>& operator=(const List<Value>& other) {
            size = other.size;
            initial = other.initial;
            capacity = other.capacity;
            Value* prevV = v;
            v = (Value*)ghnew char[sizeof(Value) * size];
            for (size_t i = 0; i < size; i++)
                new (v + i) Value(other[i]);
            for (size_t i = 0; i < size; i++)
                prevV[i].~Value();
            delete[](char*)prevV;
            return *this;
        }

        inline void deleteItems() {
            for (size_t i = 0; i < size; i++) {
                delete v[i];
                v[i].~Value();
            }
            size = 0;
        }

        inline void sort(std::function<int(const void*, const void*)> comparisonFunction = DEFAULT_COMPARISON_FUNCTION) {
            qsort(v, size, sizeof(Value), comparisonFunction);
        }
    };

}