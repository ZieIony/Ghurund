#pragma once

#include "Collection.h"
#include "List.h"

namespace Ghurund {
    template<class Value> class Array:public Collection {
    protected:
        Value* v;

    public:
        Array(size_t size) {
            this->size = size;
            v = (Value*)ghnew char[sizeof(Value) * size];
        }

        Array(const Array& t1) {
            size = t1.size;
            v = (Value*)ghnew char[sizeof(Value) * size];
            for (size_t i = 0; i < size; i++)
                new (v + i) Value(t1[i]);
        }

        Array(const std::initializer_list<Value> list) {
            size = list.size();
            v = (Value*)ghnew char[sizeof(Value) * size];
            int i = 0;
            for (auto it = list.begin(); it != list.end(); ++it, i++)
                new(v + i)Value(*it);
        }

		Array(const List<Value>& list) {
			size = list.Size;
			v = (Value*)ghnew char[sizeof(Value) * size];
			int i = 0;
			for (auto it = list.begin(); it != list.end(); ++it, i++)
				new(v + i)Value(*it);
		}

        ~Array() {
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            delete[] (char*)v;
        }

        inline void set(size_t i, const Value & e) {
            _ASSERT_EXPR(i < size, _T("Index out of bounds.\n"));
            v[i].~Value();
            new(v + i) Value(e);
        }

        inline Value& get(size_t i)const {
            _ASSERT_EXPR(i < size, _T("Index out of bounds.\n"));
            return v[i];
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

        inline size_t indexOf(const Value & item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return i;
            return size;
        }

        inline bool contains(Value & item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return true;
            return false;
        }

        const Value& operator[](size_t i)const {
            _ASSERT_EXPR(i < size, _T("Index out of bounds.\n"));
            return v[i];
        }

        Array<Value> &operator=(const Array<Value> &other) {
            size = other.size;
            initial = other.initial;
            capacity = other.capacity;
            Value *prevV = v;
            v = (Value*)ghnew char[sizeof(Value) * size];
            for (size_t i = 0; i < size; i++)
                new (v + i) Value(other[i]);
            for (size_t i = 0; i < size; i++)
                prevV[i].~Value();
            delete[] (char*)prevV;
            return *this;
        }

        inline void deleteItems() {
            for (size_t i = 0; i < size; i++) {
                delete v[i];
                v[i].~Value();
            }
        }

        inline void copyTo(Array<Value> & dest, size_t offset = 0) const {
            for (size_t i = 0; i < size; i++)
                dest.set(i + offset, v[i]);
        }
    };

}