#pragma once

#include "core/Logger.h"
#include "core/Object.h"

#include <PxFoundation.h>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include <extensions/PxDefaultAllocator.h>

using namespace physx;

namespace Ghurund {
    class Physics:public Object {
    private:
        PxDefaultErrorCallback defaultErrorCallback;
        PxDefaultAllocator defaultAllocatorCallback;
        PxFoundation* foundation = nullptr;
        PxPhysics* physics = nullptr;
        PxPvd* visualDebugger = nullptr;
        PxPvdTransport* transport = nullptr;

    public:
        ~Physics() {
            if (physics)
                physics->release();
            if (transport)
                transport->release();
            if (visualDebugger)
                visualDebugger->release();
            if (foundation)
                foundation->release();
        }

        Status init();

        PxPhysics& get() {
            return *physics;
        }

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    template<class Type>
    void setPointer2(Type *&pointer, Type *pointer2) {
        if(pointer2!=nullptr)
            pointer2->acquireReference();
        if(pointer!=nullptr)
            pointer->release();
        pointer = pointer2;
    }

    template<class Type>
    void safeRelease2(Type *&pointer) {
        if(pointer!=nullptr) {
            pointer->release();
            pointer = nullptr;
        }
    }
}