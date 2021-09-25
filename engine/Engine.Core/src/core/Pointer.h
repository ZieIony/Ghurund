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

        inline void addReference() {
            referenceCount++;
        }

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

        virtual Pointer* clone() {
            return nullptr;
        }

#ifdef _DEBUG
        static void dumpPointers();
#endif
    };

    template<class Type>
    void setPointer(Type*& pointer, Type* pointer2) {
        if (pointer2 != nullptr)
            pointer2->addReference();
        if (pointer != nullptr)
            pointer->release();
        pointer = pointer2;
    }

    template<class Type>
    void safeRelease(Type*& pointer) {
        if (pointer != nullptr) {
            pointer->release();
            pointer = nullptr;
        }
    }
}
