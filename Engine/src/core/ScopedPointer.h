#pragma once

#include "Pointer.h"

namespace Ghurund {
    template<class T> class ScopedPointer {
    private:
        T* pointer = nullptr;

    public:
        ScopedPointer() {}

        ScopedPointer(T* p) {
            pointer = p;
        }

        ~ScopedPointer() {
            if (pointer)
                pointer->release();
        }

        operator T* () {
            return pointer;
        }

        T* operator ->() {
            return pointer;
        }

        ScopedPointer<T>& operator=(T * p) {
            if (pointer)
                pointer->release();
            pointer = p;
            return *this;
        }
    };
}