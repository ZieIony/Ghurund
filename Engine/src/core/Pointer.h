#pragma once

#include "Type.h"
#include "Logger.h"
#include "Object.h"
#include "CriticalSection.h"

namespace Ghurund {

    class Pointer: public Object {
    private:
        unsigned long referenceCount;

#ifdef _DEBUG
        static Ghurund::List<Ghurund::Pointer*> pointers;
        static CriticalSection section;
#endif

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
                Logger::log(LogType::WARNING, _T("[%p] %hs release refCount=%lu. The object may have been deleted or is being released in its destructor\n"), this, typeid(*this).name(), referenceCount);
#endif
            referenceCount--;
            if(!referenceCount)
                delete this;
        }

        unsigned long getReferenceCount() const {
            return referenceCount;
        }

        __declspec(property(get = getReferenceCount)) unsigned long ReferenceCount;

#ifdef _DEBUG
        static void dumpPointers();
#endif
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
