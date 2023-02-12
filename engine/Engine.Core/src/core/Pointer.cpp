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
    CriticalSection Pointer::criticalSection;

    void Pointer::checkReferenceCount() {
        if (referenceCount == 0) {
            const auto& info = typeid(*this);
            auto text = std::format(
                _T("[{:#x}] {} ({}) release refCount={}. The object may have been deleted or is being released in its destructor\n"),
                (address_t)this, AString(GET_TYPE().Name), AString(info.name()), referenceCount
            );
            Logger::log(LogType::WARNING, text.c_str());
        }
    }
#endif

    Pointer::~Pointer() {
#ifdef _DEBUG
        criticalSection.enter();
        pointers.remove(this);
        criticalSection.leave();

        if (referenceCount) {
            const auto& info = typeid(*this);
            if (referenceCount == 1) {
                auto text = std::format(
                    _T("[{:#x}] {} ({}) delete refCount=1. This deletion could be replaced with Pointer::release() call\n"),
                    (address_t)this, AString(GET_TYPE().Name), AString(info.name())
                );
                Logger::log(LogType::WARNING, text.c_str());
            } else {
                auto text = std::format(
                    _T("[{:#x}] {} ({}) delete refCount={}. The object may still be in use. Consider replacing deletion with Pointer::release() call\n"),
                    (address_t)this, AString(GET_TYPE().Name), AString(info.name()), referenceCount
                );
                Logger::log(LogType::WARNING, text.c_str());
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
        criticalSection.enter();
        pointers.add(this);
        criticalSection.leave();
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
        criticalSection.enter();
        if (pointers.Empty) {
            Logger::log(LogType::INFO, _T("no allocated pointers\n"));
        } else {
            Logger::log(LogType::INFO, std::format(_T("allocated pointers ({}):\n"), pointers.Size).c_str());
            for (Pointer* p : pointers) {
                const auto& info = typeid(*p);
                auto text = std::format(_T("[{:#x}] {} ({}) refCount={}\n"), (address_t)p, p->toString(), AString(info.name()), p->ReferenceCount);
                Logger::print(LogType::INFO, text.c_str());
                for (StackTrace::Entry& e : p->stacktrace) {
                    if (e.fileName.Empty || !e.address || e.name.Empty)
                        continue;
                    auto entryText = std::format(_T("{0}({1:d}): [{2:#x} {3}(..)]\n"), e.fileName, e.fileLine, e.address, e.name);
                    Logger::print(LogType::INFO, entryText.c_str());
                }
                Logger::print(LogType::INFO, _T("\n"));
            }
        }
        criticalSection.leave();
    }
#endif
}