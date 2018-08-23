#pragma once

#include "Ghurund.h"
#include "Type.h"

namespace Ghurund {

    void dumpPointers();

    class Pointer {
    private:
        unsigned long referenceCount;

    protected:
        Pointer(const Pointer &pointer);

    public:
        Pointer();

        virtual ~Pointer();

        inline void addReference() {
            referenceCount++;
        }

        inline void release() {
            referenceCount--;
            if(!referenceCount)
                delete this;
        }

        unsigned long getReferenceCount() const {
            return referenceCount;
        }

        __declspec(property(get = getReferenceCount)) unsigned long ReferenceCount;

        virtual const Type &getType() const = 0;

        __declspec(property(get = getType)) Ghurund::Type &Type;
    };

    template<class Type>
    void setPointer(Type *&pointer, Type *pointer2) {
        if(pointer2!=nullptr)
            pointer2->addReference();
        if(pointer!=nullptr)
            pointer->release();
        pointer = pointer2;
    }
}
