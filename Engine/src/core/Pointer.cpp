#include "Pointer.h"
#include <typeinfo>
#include "Logger.h"
#include "collection/List.h"

Ghurund::List<Ghurund::Pointer*> pointers;

namespace Ghurund {
    void dumpPointers() {
#ifdef _DEBUG
        for(unsigned int i = 0; i<pointers.getSize(); i++) {
            Pointer *p = pointers[i];
            Logger::log(_T("allocated pointer: [%#x] %hs refCount=%lu\n"), (int)p, typeid(*p).name(), p->ReferenceCount);
        }
#endif
    }

    Pointer::Pointer() {
        referenceCount = 1;
#ifdef _DEBUG
        pointers.add(this);
#endif
    }

    Pointer::Pointer(const Pointer &pointer) {
        referenceCount = 1;
    }

    Pointer::~Pointer() {
#ifdef _DEBUG
        if(referenceCount) {
            if(referenceCount==1) {
                Logger::log(_T("[%#x] %hs delete refCount=1. This deletion could be replaced with Pointer::release() call\n"), (int)this, typeid(*this).name());
            } else {
                Logger::log(_T("[%#x] %hs delete refCount=%lu. The object may still be in use. Consider replacing deletion with Pointer::release() call\n"), (int)this, typeid(*this).name(), referenceCount);
            }
        }
        pointers.remove(this);
#endif
    }
}