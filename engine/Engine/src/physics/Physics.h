#pragma once

#include "Status.h"
#include "application/Feature.h"

#pragma warning(push, 0)
#include <PxFoundation.h>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include <extensions/PxDefaultAllocator.h>
#pragma warning(pop)

#ifdef _WIN64
#pragma comment(lib, "PhysX_64.lib")
#pragma comment(lib, "PhysXCommon_64.lib")
#pragma comment(lib, "PhysXFoundation_64.lib")
#pragma comment(lib, "PhysXExtensions_static_64.lib")
#pragma comment(lib, "PhysXPvdSDK_static_64.lib")
#else
#pragma comment(lib, "PhysX_32.lib")
#pragma comment(lib, "PhysXCommon_32.lib")
#pragma comment(lib, "PhysXFoundation_32.lib")
#pragma comment(lib, "PhysXExtensions_static_32.lib")
#pragma comment(lib, "PhysXPvdSDK_static_32.lib")
#endif

namespace Ghurund {
    class Application;
}

#include "reflection_a03568f5_3f80_416f_aafa_4cf87e702942.h"

namespace Ghurund::Physics {
    using namespace physx;

    class Physics:public Feature {
        reflection_a03568f5_3f80_416f_aafa_4cf87e702942

    private:
        PxDefaultErrorCallback defaultErrorCallback;
        PxDefaultAllocator defaultAllocatorCallback;
        PxFoundation* foundation = nullptr;
        PxPhysics* physics = nullptr;
        PxPvd* visualDebugger = nullptr;
        PxPvdTransport* transport = nullptr;

    public:
        virtual Status init() override;

        virtual void uninit() override {
            if (physics)
                physics->release();
            if (transport)
                transport->release();
            if (visualDebugger)
                visualDebugger->release();
            if (foundation)
                foundation->release();
        }

        PxPhysics& get() {
            return *physics;
        }
    };

    template<class Type>
    void setPointer2(Type*& pointer, Type* pointer2) {
        if (pointer2 != nullptr)
            pointer2->acquireReference();
        if (pointer != nullptr)
            pointer->release();
        pointer = pointer2;
    }

    template<class Type>
    void safeRelease2(Type*& pointer) {
        if (pointer != nullptr) {
            pointer->release();
            pointer = nullptr;
        }
    }
}