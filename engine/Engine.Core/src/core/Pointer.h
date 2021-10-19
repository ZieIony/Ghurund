#pragma once

#include "Object.h"

#ifdef _DEBUG
#include "core/StackTrace.h"
#include "core/collection/List.h"
#endif

namespace Ghurund::Core {

    class Pointer: public Object {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

    private:
        mutable unsigned int referenceCount = 1;

#ifdef _DEBUG
        static List<Pointer*> pointers;

        List<StackTrace::Entry> stacktrace;

        void checkReferenceCount();
#endif

    protected:
        Pointer(const Pointer& pointer) = delete;

        virtual ~Pointer() = 0;

    public:
        Pointer();

        /**
         * @brief Increases reference count by 1.
        */
        inline void addReference() {
            referenceCount++;
        }

        /**
         * @brief Decreases reference count of this object by one. If the reference count reaches 0, the object is deleted.
        */
        inline void release() {
#ifdef _DEBUG
            checkReferenceCount();
#endif
            referenceCount--;
            if (!referenceCount)
                delete this;
        }

        unsigned long getReferenceCount() const {
            return referenceCount;
        }

        __declspec(property(get = getReferenceCount)) unsigned long ReferenceCount;

        virtual String toString() const override;

#ifdef _DEBUG
        static void dumpPointers();
#endif
    };

    /**
     * @brief Safely sets a Pointer object to a new value. The previous Pointer has its reference counter decreased by one,
     * and the new Pointer has its reference counter increased by one.
     * @tparam Type
     * @param pointer A reference to a Pointer address to assign another Pointer to. The address can be null.
     * @param pointer2 A Pointer address to assign to 'pointer'. Can be null.
    */
    template<class Type>
    void setPointer(Type*& pointer, Type* pointer2) {
        if (pointer2 != nullptr)
            pointer2->addReference();
        if (pointer != nullptr)
            pointer->release();
        pointer = pointer2;
    }

    /**
     * @brief Safely releases and clears a Pointer object.
     * @tparam Type
     * @param pointer
    */
    template<class Type>
    void safeRelease(Type*& pointer) {
        if (pointer != nullptr) {
            pointer->release();
            pointer = nullptr;
        }
    }
}
