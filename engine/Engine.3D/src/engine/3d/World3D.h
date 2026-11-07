#pragma once

#include "audio/AudioSystem3D.h"
#include "physics/PhysicsSystem3D.h"
#include "engine/ecs/SystemCollection.h"
#include "engine/application/GameApplication.h"
#include "engine/ecs/World.h"
#include "engine/ecs/Scene.h"

namespace Ghurund::Core {
	class Application;
}

namespace Ghurund::Engine::_3D {
	class World3D:public World {
	private:
		IntrusivePointer<AudioSystem3D> audioSystem;
		IntrusivePointer<PhysicsSystem3D> physicsSystem;
		SystemCollection systems;
		Scene* scene = nullptr;

	protected:
		virtual void onInit() override;

		inline void deinitWorld3D() {
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
			if (scene)
				scene->release();
		}

		inline AudioSystem3D* getAudioSystem() {
			return audioSystem.get();
		}

		__declspec(property(get = getAudioSystem)) AudioSystem3D* AudioSystem;

		inline PhysicsSystem3D& getPhysicsSystem() {
			return physicsSystem.ref();
		}

		__declspec(property(get = getPhysicsSystem)) PhysicsSystem3D& PhysicsSystem;

		inline Scene* getScene() {
			return scene;
		}

		inline void setScene(Scene* scene) {
			setPointer(this->scene, scene);
		}

		__declspec(property(get = getScene, put = setScene)) Scene* Scene;
	};
}
