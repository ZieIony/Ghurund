#include "ghcpch.h"
#include "RefCountedObject.h"

#include "core/collection/List.h"
#include "core/logging/Formatter.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

#include <typeinfo>
#include <format>

namespace Ghurund::Core {
#ifdef _DEBUG
    List<RefCountedObject*> RefCountedObject::pointers;
    CriticalSection RefCountedObject::criticalSection;
    bool RefCountedObject::pointersListResizeLocked = false;

    void RefCountedObject::checkReferenceCount() const {
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

    RefCountedObject::~RefCountedObject() {
#ifdef _DEBUG
        criticalSection.enter();
        pointers.remove(this);
        criticalSection.leave();

        if (referenceCount) {
            const auto& info = typeid(*this);
            if (referenceCount == 1) {
                auto text = std::format(
                    _T("[{:#x}] {} ({}) delete refCount=1. This deletion could be replaced with RefCountedObject::release() call\n"),
                    (address_t)this, AString(GET_TYPE().Name), AString(info.name())
                );
                Logger::log(LogType::WARNING, text.c_str());
            } else {
                auto text = std::format(
                    _T("[{:#x}] {} ({}) delete refCount={}. The object may still be in use. Consider replacing deletion with RefCountedObject::release() call\n"),
                    (address_t)this, AString(GET_TYPE().Name), AString(info.name()), referenceCount
                );
                Logger::log(LogType::WARNING, text.c_str());
            }
        }
#endif
    }

    const Ghurund::Core::Type& RefCountedObject::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<RefCountedObject>(NAMESPACE_NAME, GH_STRINGIFY(RefCountedObject))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    RefCountedObject::RefCountedObject() {
#ifdef _DEBUG
        {
            SectionLock lock(criticalSection);
            if (pointers.Size == pointers.Capacity) {
                if (pointersListResizeLocked)
                    throw InvalidStateException("cannot resize pointers list");
                pointers.resize((size_t)(pointers.Capacity * 1.6f));
            }
            pointers.add(this);
        }
        StackTrace stacktrace(GetCurrentProcess());
        // skip self and the app entry point
        for (uint16_t i = 1; i < std::min(4ui16, stacktrace.Size); i++)
            this->stacktrace.add(stacktrace[i]);
#endif
    }

    String RefCountedObject::toString() const {
        return String(std::format(_T("{} (refs: {})"), __super::toString(), referenceCount).c_str());
    }

#ifdef _DEBUG
    void RefCountedObject::dumpPointers() {
        SectionLock lock(criticalSection);
        if (pointers.Empty) {
            Logger::log(LogType::INFO, _T("no allocated pointers\n"));
        } else {
            Logger::log(LogType::INFO, std::format(_T("allocated pointers ({}):\n"), pointers.Size).c_str());
            for (RefCountedObject* p : pointers) {
                const auto& info = typeid(*p);
                auto text = std::format(_T("\n[{:#x}] {} ({}) refCount={}\n"), (address_t)p, p->toString(), AString(info.name()), p->ReferenceCount);
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
    }
#endif
}