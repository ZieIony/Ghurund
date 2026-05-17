#pragma once

#include "scene/Scene3D.h"
#include "audio/AudioSystem3D.h"
#include "physics/PhysicsSystem3D.h"
#include "engine/game/system/SystemCollection.h"
#include "engine/application/GameApplication.h"

namespace Ghurund::Core {
	class Application;
}

namespace Ghurund::Engine::_3D {
	class World3D:public Initializable, public Noncopyable {
	private:
		IntrusivePointer<AudioSystem3D> audioSystem;
		IntrusivePointer<PhysicsSystem3D> physicsSystem;
		SystemCollection systems;
		IntrusivePointer<Scene3D> scene;

	protected:
		virtual void onInit() override;

		inline void uninitWorld3D() {
			scene.set(nullptr);
			systems.uninit();
			physicsSystem.set(nullptr);
			audioSystem.set(nullptr);
		}

		virtual void onUninit() override;

	public:
		GameApplication& app;
		IGraphics3DContext& context;
		
		World3D(
			GameApplication& app,
			IGraphics3DContext& context
		):app(app), context(context), systems(app.GameObjects) {
		}

		~World3D() {
			if (IsInitialized)
				uninitWorld3D();
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

		template<Derived<Entity3D> T>
		inline CoroutineTask<IntrusivePointer<T>> spawnEntity() {
			auto entity = makeIntrusive<T>(*this);
			co_await entity->init();
			scene->add(entity);
			co_return entity;
		}

		inline void draw(RenderGroup& group) {
			scene->draw(group);
		}
	};
}
