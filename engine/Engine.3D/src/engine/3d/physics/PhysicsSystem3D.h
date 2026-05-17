#pragma once

#include "Physics.h"

#include "engine/game/system/System.h"

#pragma warning(push, 0)
#include <extensions/PxDefaultCpuDispatcher.h>
#include <PxPhysicsAPI.h>
#include <PxScene.h>
#pragma warning(pop)

namespace Ghurund::Engine::_3D {
	using namespace physx;

	class PhysicsSystem3D:public System {
	private:
		PxDefaultCpuDispatcher* dispatcher = nullptr;
		PxScene* scene = nullptr;

	public:
		void init(Physics& physics) {
			PxSceneDesc sceneDesc(physics.get().getTolerancesScale());
			sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
			dispatcher = PxDefaultCpuDispatcherCreate(0);
			sceneDesc.cpuDispatcher = dispatcher;
			sceneDesc.filterShader = PxDefaultSimulationFilterShader;
			scene = physics.get().createScene(sceneDesc);
		}

		void update(float dt) {
			scene->simulate(dt);
			scene->fetchResults(true);
		}
	};
}
