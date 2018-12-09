#pragma once

#include "Ghurund.h"
#include "Type.h"
#include "Logger.h"
#include "Object.h"

namespace Ghurund {

    void dumpPointers();

    class Pointer: public Object {
    private:
        unsigned long referenceCount;

    protected:
        Pointer(const Pointer &pointer);

    public:
        Pointer();

        virtual ~Pointer() = 0;

        inline void addReference() {
            referenceCount++;
        }

        inline void release() {
#ifdef _DEBUG
            if(referenceCount==0)
                Logger::log(_T("[%#x] %hs release refCount=%lu. The object may have been deleted or is being released in its destructor\n"), (int)this, typeid(*this).name(), referenceCount);
#endif
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

    template<class Type>
    void safeRelease(Type *&pointer) {
        if(pointer!=nullptr) {
            pointer->release();
            pointer = nullptr;
        }
    }
}
