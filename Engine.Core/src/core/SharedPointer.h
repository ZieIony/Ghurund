#pragma once

#include "Pointer.h"
#include "Common.h"

namespace Ghurund {
    template<class T>
    concept IsPointer = std::is_base_of<Pointer, T>::value;

    template<IsPointer T>
    class SharedPointer {
    private:
        T* pointer = nullptr;

    public:
        SharedPointer() {}

        SharedPointer(const SharedPointer& sp) {
            pointer = sp.pointer;
            if (pointer)
                pointer->addReference();
        }

        SharedPointer(T* p) {
            pointer = p;
        }

        ~SharedPointer() {
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

        SharedPointer<T>& operator=(T* p) {
            if (pointer)
                pointer->release();
            pointer = p;
            return *this;
        }

        SharedPointer<T>& operator=(const SharedPointer<T>& sp) {
            setPointer(pointer, sp.pointer);
            return *this;
        }
    };

    template<IsPointer T, typename... Args>
    SharedPointer<T> makeShared(Args&&... args) {
        return ghnew T(std::forward<Args>(args)...);
    }
}