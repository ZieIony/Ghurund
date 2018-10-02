#include "Pointer.h"
#include <typeinfo>
#include "Logger.h"
#include "collection/List.h"

Ghurund::List<Ghurund::Pointer*> pointers;

namespace Ghurund {
    void dumpPointers() {
#ifdef _DEBUG
        for(unsigned int i = 0; i<pointers.getSize(); i++) {
            tchar text[300];
            Pointer *p = pointers[i];
            _stprintf_s(text, 300, _T("unallocated pointer: \n[%#x] %hs refCount=%i\n"), (int)p, typeid(*p).name(), p->ReferenceCount);
            Logger::log(text);
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
            tchar text[200];
            String name = typeid(*this).name();
            if(referenceCount==1) {
                _stprintf_s(text, 200, _T("[%#x] %s delete refCount=%i. This deletion could be replaced with Pointer::release() call"), (int)this, name.getData(), referenceCount);
            } else {
                _stprintf_s(text, 200, _T("[%#x] %s delete refCount=%i. The object may still be in use. Consider replacing deletion with Pointer::release() call"), (int)this, name.getData(), referenceCount);
            }
            Logger::log(text);
        }
        pointers.remove(this);
#endif
    }
}