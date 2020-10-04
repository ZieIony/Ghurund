#pragma once

#include "Pointer.h"

namespace Ghurund {
    template<class T>
    requires IsPointer<T>
    class ScopedPointer {
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

        const T* operator ->() const {
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