#pragma once

#include "scene/Scene2D.h"
#include "audio/AudioSystem2D.h"
#include "physics/PhysicsSystem2D.h"
#include "engine/ecs/SystemCollection.h"
#include "engine/ecs/World.h"
#include "engine/application/GameApplication.h"

namespace Ghurund::Core {
	class Application;
}

namespace Ghurund::Engine::_2D {
	class World2D:public World {
	private:
		IntrusivePointer<AudioSystem2D> audioSystem;
		IntrusivePointer<PhysicsSystem2D> physicsSystem;
		SystemCollection systems;
		IntrusivePointer<Scene2D> scene;

	protected:
		virtual void onInit() override;

		inline void uninitWorld2D() {
			scene.set(nullptr);
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

		inline Scene2D& getScene() {
			return scene.ref();
		}

		__declspec(property(get = getScene)) Scene2D& Scene;
	};
}
