#pragma once

#include "Pointer.h"
#include "Common.h"
#include "Concepts.h"

namespace Ghurund::Core {
    template<typename T>
    class SharedPointer {
    private:
        T* pointer = nullptr;

    public:
        SharedPointer() {}

        SharedPointer(const SharedPointer& other) {
            pointer = other.pointer;
            if (pointer)
                pointer->addReference();
        }

        SharedPointer(SharedPointer&& other) noexcept {
            pointer = other.pointer;
            other.pointer = nullptr;
        }

        SharedPointer(T* p) {
            pointer = p;
        }

        ~SharedPointer() {
            if (pointer)
                pointer->release();
        }

        T& operator*() {
            return *pointer;
        }

        T* operator&() {
            return pointer;
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

        SharedPointer<T>& operator=(const SharedPointer<T>& other) {
            setPointer(pointer, other.pointer);
            return *this;
        }

        SharedPointer<T>& operator=(SharedPointer<T>&& other) {
            pointer = other.pointer;
            other.pointer = nullptr;
            return *this;
        }

        bool operator==(const SharedPointer<T>& other) const {
            return pointer == other.pointer;
        }
    };

    template<typename T, typename... Args>
    SharedPointer<T> makeShared(Args&&... args) {
        return ghnew T(std::forward<Args>(args)...);
    }
}