#include "Pointer.h"
#include <typeinfo>
#include "Logger.h"
#include "collection/List.h"

namespace Ghurund {
    Ghurund::List<Ghurund::Pointer*> Pointer::pointers;
    CriticalSection Pointer::section;

    Pointer::Pointer() {
        referenceCount = 1;
#ifdef _DEBUG
        section.enter();
        pointers.add(this);
        section.leave();
#endif
    }

    Pointer::Pointer(const Pointer &pointer) {
        referenceCount = 1;
    }

    Pointer::~Pointer() {
#ifdef _DEBUG
        section.enter();
        if(referenceCount) {
            if(referenceCount==1) {
                Logger::log(LogType::WARNING, _T("[%p] %hs delete refCount=1. This deletion could be replaced with Pointer::release() call\n"), this, typeid(*this).name());
            } else {
                Logger::log(LogType::WARNING, _T("[%p] %hs delete refCount=%lu. The object may still be in use. Consider replacing deletion with Pointer::release() call\n"), this, typeid(*this).name(), referenceCount);
            }
        }
        pointers.remove(this);
        section.leave();
#endif
    }

    void Pointer::dumpPointers() {
#ifdef _DEBUG
        section.enter();
        for(unsigned int i = 0; i<pointers.getSize(); i++) {
            Pointer *p = pointers[i];
            Logger::log(LogType::INFO, _T("allocated pointer: [%p] %hs refCount=%lu\n"), p, typeid(*p).name(), p->ReferenceCount);
        }
        section.leave();
#endif
    }
}