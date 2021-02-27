#pragma once

#include "Object.h"

namespace Ghurund {

    class Pointer: public Object {
    private:
        unsigned int referenceCount = 1;

#ifdef _DEBUG
        void checkReferenceCount();
#endif

    protected:
        Pointer(const Pointer& pointer) = delete;

        virtual ~Pointer() = 0;

        static const Ghurund::Type& GET_TYPE();

    public:
        Pointer() {}

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
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
