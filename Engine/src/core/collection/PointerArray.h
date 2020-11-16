#pragma once

#include "Array.h"

namespace Ghurund {
    template<class Value>
    class PointerArray:public Array<Value> {
    public:
        PointerArray(size_t size):Array<Value>(size) {
            memset(Array<Value>::v, 0, sizeof(Pointer*) * size);
        }

        ~PointerArray() {
            for (size_t i = 0; i < Array<Value>::size; i++)
                if (Array<Value>::v[i] != nullptr)
                    Array<Value>::v[i]->release();
        }

        inline void set(size_t i, const Value& item) {
            if (Array<Value>::v[i] != nullptr)
                Array<Value>::v[i]->release();
            Array<Value>::set(i, item);
            if (item != nullptr)
                item->addReference();
        }

        inline void releaseItems() {
            for (size_t i = 0; i < Array<Value>::size; i++) {
                if (Array<Value>::v[i] != nullptr)
                    Array<Value>::v[i]->release();
            }
        }

        inline void copyTo(PointerArray<Value>& dest, size_t offset = 0) const {
            for (size_t i = 0; i < Array<Value>::size; i++)
                dest.set(i + offset, Array<Value>::v[i]);
        }
    };

}