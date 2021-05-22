#pragma once

#include "core/resource/Resource.h"
#include "physics/Physics.h"

#pragma warning(push, 0)
#include <PxScene.h>
#include <extensions/PxDefaultCpuDispatcher.h>
#pragma warning(pop)

namespace Ghurund::Physics {
	using namespace physx;

	class PhysicsSystem {
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