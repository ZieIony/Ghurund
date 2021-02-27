#include "Pointer.h"

#include "core/collection/List.h"
#include "core/logging/Formatter.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

#include <typeinfo>
#include <tchar.h>

namespace Ghurund {
#ifdef _DEBUG
    void Pointer::checkReferenceCount() {
        if (referenceCount == 0) {
            const auto& info = typeid(*this);
            Logger::log(LogType::WARNING, _T("[{}] {} release refCount={}. The object may have been deleted or is being released in its destructor\n"), (address_t)this, String(info.name()), referenceCount);
        }
    }
#endif

    Pointer::~Pointer() {
#ifdef _DEBUG
        if(referenceCount) {
            if(referenceCount==1) {
                Logger::log(LogType::WARNING, _T("[%p] %hs delete refCount=1. This deletion could be replaced with Pointer::release() call\n"), (void*)this, typeid(*this).name());
            } else {
                Logger::log(LogType::WARNING, _T("[%p] %hs delete refCount=%lu. The object may still be in use. Consider replacing deletion with Pointer::release() call\n"), (void*)this, typeid(*this).name(), referenceCount);
            }
        }
#endif
    }
    
    const Ghurund::Type& Pointer::GET_TYPE() {
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Pointer))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}