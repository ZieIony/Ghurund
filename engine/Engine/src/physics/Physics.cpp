#include "ghpch.h"
#include "Physics.h"

#include "core/Exceptions.h"
#include "core/reflection/TypeBuilder.h"
#include "core/logging/Logger.h"

#include <PxPhysicsAPI.h>

namespace Ghurund::Physics {
    using namespace Ghurund::Core;
    using namespace physx;

    const Ghurund::Core::Type& Physics::GET_TYPE() {

        static const auto CONSTRUCTOR = Constructor<Physics>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Physics>("Ghurund::Physics", "Physics")
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Physics::onInit() {
        foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback, defaultErrorCallback);
        if (!foundation) {
            Logger::log(LogType::ERR0R, _T("PxCreateFoundation failed\n"));
            throw CallFailedException();
        }

        bool recordMemoryAllocations = true;

        const char* PVD_HOST = "127.0.0.1";	//Set this to the IP address of the system running the PhysX Visual Debugger that you want to connect to.
        visualDebugger = PxCreatePvd(*foundation);
        transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
        visualDebugger->connect(*transport, PxPvdInstrumentationFlag::eALL);


        physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), recordMemoryAllocations, visualDebugger);
        if (!physics) {
            Logger::log(LogType::ERR0R, _T("PxCreatePhysics failed\n"));
            throw CallFailedException();
        }
    }
}