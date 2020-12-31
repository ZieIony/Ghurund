#pragma once

#include "application/log/Logger.h"
#include "Object.h"
#include "core/threading/CriticalSection.h"
#include "core/reflection/Type.h"

#include <typeinfo>

namespace Ghurund {

    class Pointer: public Object {
    private:
        unsigned long referenceCount;

#ifdef _DEBUG
        static Ghurund::List<Ghurund::Pointer*> pointers;
        static CriticalSection section;
#endif

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Pointer))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    protected:
        Pointer(const Pointer& pointer);

        virtual ~Pointer() = 0;

    public:
        Pointer();

        inline void addReference() {
            referenceCount++;
        }

        inline void release() {
#ifdef _DEBUG
            if (referenceCount == 0) {
                const auto& info = typeid(*this);
                Logger::log(LogType::WARNING, _T("[{}] {} release refCount={}. The object may have been deleted or is being released in its destructor\n"), (address_t)this, String(info.name()), referenceCount);
            }
#endif
            referenceCount--;
            if (!referenceCount)
                delete this;
        }

        unsigned long getReferenceCount() const {
            return referenceCount;
        }

        __declspec(property(get = getReferenceCount)) unsigned long ReferenceCount;

#ifdef _DEBUG
        static void dumpPointers();
#endif

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    template<class T>
    concept IsPointer = std::is_base_of<Pointer, T>::value;

    template<class Type>
    void setPointer(Type*& pointer, Type* pointer2) {
        if (pointer2 != nullptr)
            pointer2->addReference();
        if (pointer != nullptr)
            pointer->release();
        pointer = pointer2;
    }

    template<class Type>
    void safeRelease(Type*& pointer) {
        if (pointer != nullptr) {
            pointer->release();
            pointer = nullptr;
        }
    }
}
