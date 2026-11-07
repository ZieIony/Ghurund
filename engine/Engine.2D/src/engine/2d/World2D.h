#pragma once

#include "engine/ecs/SystemCollection.h"
#include "engine/ecs/World.h"
#include "engine/ecs/Scene.h"
#include "engine/application/GameApplication.h"
#include "engine/2d/audio/AudioSystem2D.h"
#include "engine/2d/physics/PhysicsSystem2D.h"

namespace Ghurund::Core {
	class Application;
}

namespace Ghurund::Engine::_2D {
	class World2D:public World {
	private:
		IntrusivePointer<AudioSystem2D> audioSystem;
		IntrusivePointer<PhysicsSystem2D> physicsSystem;
		SystemCollection systems;
		Scene* scene = nullptr;

	protected:
		virtual void onInit() override;

		inline void uninitWorld2D() {
			safeRelease(scene);
			systems.clear();
			physicsSystem.set(nullptr);
			audioSystem.set(nullptr);
		}

		virtual void onDeinit() override;

	public:
		World2D(
			GameApplication& app
		):World(app) {
		}

		~World2D() {
			if (IsInitialized)
				uninitWorld2D();
		}

		inline AudioSystem2D* getAudioSystem() {
			return audioSystem.get();
		}

		__declspec(property(get = getAudioSystem)) AudioSystem2D* AudioSystem;

		inline PhysicsSystem2D& getPhysicsSystem() {
			return physicsSystem.ref();
		}

		__declspec(property(get = getPhysicsSystem)) PhysicsSystem2D& PhysicsSystem;

		inline Scene* getScene() {
			return scene;
		}

		inline void setScene(Scene* scene) {
			setPointer(this->scene, scene);
		}

		__declspec(property(get = getScene)) Scene* Scene;
	};
}
