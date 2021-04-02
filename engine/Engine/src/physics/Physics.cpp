#include "ghpch.h"
#include "Physics.h"

namespace Ghurund::Physics {
    const Ghurund::Type& Physics::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Physics>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Physics))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(Object::TYPE);

        return TYPE;
    }

    Status Physics::init() {
        foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback, defaultErrorCallback);
        if (!foundation)
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("PxCreateFoundation failed\n"));

        bool recordMemoryAllocations = true;

        const char* PVD_HOST = "127.0.0.1";	//Set this to the IP address of the system running the PhysX Visual Debugger that you want to connect to.
        visualDebugger = PxCreatePvd(*foundation);
        transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
        visualDebugger->connect(*transport, PxPvdInstrumentationFlag::eALL);


        physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), recordMemoryAllocations, visualDebugger);
        if (!physics)
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("PxCreatePhysics failed\n"));

        return Status::OK;
    }
}