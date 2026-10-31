#pragma once

#include "scene/Scene3D.h"
#include "audio/AudioSystem3D.h"
#include "physics/PhysicsSystem3D.h"
#include "engine/ecs/SystemCollection.h"
#include "engine/application/GameApplication.h"
#include "engine/ecs/World.h"

namespace Ghurund::Core {
	class Application;
}

namespace Ghurund::Engine::_3D {
	class World3D:public World {
	private:
		IntrusivePointer<AudioSystem3D> audioSystem;
		IntrusivePointer<PhysicsSystem3D> physicsSystem;
		SystemCollection systems;
		IntrusivePointer<Scene3D> scene;

	protected:
		virtual void onInit() override;

		inline void deinitWorld3D() {
			scene.set(nullptr);
			systems.clear();
			physicsSystem.set(nullptr);
			audioSystem.set(nullptr);
		}

		virtual void onDeinit() override;

	public:
		World3D(
			GameApplication& app
		):World(app) {
		}

		~World3D() {
			if (IsInitialized)
				deinitWorld3D();
		}

		inline AudioSystem3D* getAudioSystem() {
			return audioSystem.get();
		}

		__declspec(property(get = getAudioSystem)) AudioSystem3D* AudioSystem;

		inline PhysicsSystem3D& getPhysicsSystem() {
			return physicsSystem.ref();
		}

		__declspec(property(get = getPhysicsSystem)) PhysicsSystem3D& PhysicsSystem;

		inline Scene3D& getScene() {
			return scene.ref();
		}

		__declspec(property(get = getScene)) Scene3D& Scene;
	};
}
