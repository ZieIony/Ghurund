#pragma once

#include "Pointer.h"
#include "Common.h"
#include "core/concepts/Concepts.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    template<typename T>
    class SharedPointer {
    private:
        T* pointer = nullptr;

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Type TYPE = TypeBuilder<SharedPointer<T>>(Ghurund::Core::NAMESPACE_NAME, "SharedPointer").withTemplateParams<T>();
            return TYPE;
        }

        inline static const Type& TYPE = GET_TYPE();

        constexpr SharedPointer():pointer(nullptr) {}

        SharedPointer(const SharedPointer<T>& other) {
            pointer = other.get();
            if (pointer)
                pointer->addReference();
        }

        SharedPointer(SharedPointer<T>&& other) noexcept {
            pointer = other.pointer;
            other.pointer = nullptr;
        }

        explicit SharedPointer(T* p) {
            pointer = p;
        }

        ~SharedPointer() {
            if (pointer)
                pointer->release();
        }

        inline T* get() const {
            return pointer;
        }

        inline void set(T* p) {
            if (pointer)
                pointer->release();
            pointer = p;
        }

        inline T* operator ->() {
            return pointer;
        }

        inline const T* operator ->() const {
            return pointer;
        }

        inline SharedPointer<T>& operator=(const SharedPointer<T>& other) {
            setPointer(pointer, other.pointer);
            return *this;
        }

        inline SharedPointer<T>& operator=(SharedPointer<T>&& other) noexcept {
            if(pointer)
                pointer->release();
            pointer = other.pointer;
            other.pointer = nullptr;
            return *this;
        }

        inline bool operator==(const SharedPointer<T>& other) const {
            return pointer == other.pointer;
        }

        inline bool operator==(const nullptr_t& other) const {
            return pointer == nullptr;
        }
    };

    template<typename T, typename... Args>
    SharedPointer<T> makeShared(Args&&... args) {
        return SharedPointer(ghnew T(std::forward<Args>(args)...));
    }

}