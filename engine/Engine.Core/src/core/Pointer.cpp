#include "ghcpch.h"
#include "Pointer.h"

#include "core/collection/List.h"
#include "core/logging/Formatter.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

#include <typeinfo>
#include <format>

namespace Ghurund::Core {
#ifdef _DEBUG
    List<Pointer*> Pointer::pointers;

    void Pointer::checkReferenceCount() {
        if (referenceCount == 0) {
            const auto& info = typeid(*this);
            Logger::log(LogType::WARNING, _T("[{:#x}] {} ({}) release refCount={}. The object may have been deleted or is being released in its destructor\n"), (address_t)this, AString(GET_TYPE().Name), AString(info.name()), referenceCount);
        }
    }
#endif

    Pointer::~Pointer() {
#ifdef _DEBUG
        pointers.remove(this);

        if (referenceCount) {
            const auto& info = typeid(*this);
            if (referenceCount == 1) {
                Logger::log(LogType::WARNING, _T("[{:#x}] {} ({}) delete refCount=1. This deletion could be replaced with Pointer::release() call\n"), (address_t)this, AString(GET_TYPE().Name), AString(info.name()));
            } else {
                Logger::log(LogType::WARNING, _T("[{:#x}] {} ({}) delete refCount={}. The object may still be in use. Consider replacing deletion with Pointer::release() call\n"), (address_t)this, AString(GET_TYPE().Name), AString(info.name()), referenceCount);
            }
        }
#endif
    }

    const Ghurund::Core::Type& Pointer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(Pointer))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Pointer::Pointer() {
#ifdef _DEBUG
        pointers.add(this);
        StackTrace stacktrace(GetCurrentProcess());
        // skip self and the app entry point
        for (uint16_t i = 1; i < stacktrace.Size - 6; i++)
            this->stacktrace.add(stacktrace[i]);
#endif
    }

    String Pointer::toString() const {
        return String(std::format(_T("{} (refs: {})"), __super::toString(), referenceCount).c_str());
    }

#ifdef _DEBUG
    void Pointer::dumpPointers() {
        if (pointers.Empty) {
            Logger::log(LogType::INFO, _T("no allocated pointers\n"));
        } else {
            Logger::log(LogType::INFO, _T("allocated pointers:\n"));
            for (Pointer* p : pointers) {
                const auto& info = typeid(*p);
                Logger::print(LogType::INFO, _T("[{:#x}] {} ({}) refCount={}\n"), (address_t)p, AString(p->getType().Name), AString(info.name()), p->ReferenceCount);
                for (StackTrace::Entry& e : p->stacktrace)
                    Logger::print(LogType::INFO, _T("{0}({1:d}): [{2:#x} {3}(..)]\n"), e.fileName, e.fileLine, e.address, e.name);
                Logger::print(LogType::INFO, _T("\n"));
            }
        }
    }
#endif
}