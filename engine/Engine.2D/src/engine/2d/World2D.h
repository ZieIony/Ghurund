#pragma once

#include "scene/Scene2D.h"
#include "audio/AudioWorld2D.h"
#include "physics/Simulation2D.h"

namespace Ghurund::Core {
	class Application;
}

namespace Ghurund::Engine::_2D {
	class World2D:public Noncopyable {
	public:
		Application* app;
		IGraphics2DContext* context;
		Scene2D* scene;
		AudioWorld2D* audioWorld;
		Simulation2D* simulation;

		template<Derived<Entity2D> T>
		inline CoroutineTask<IntrusivePointer<T>> spawnEntity() {
			auto entity = makeIntrusive<T>(*this);
			co_await entity->init();
			scene->Entities.add(entity);
			co_return entity;
		}

		inline void fixedUpdate(const Timer& timer) {
			simulation->simulate(timer.FixedFrameTime);
			scene->fixedUpdate(timer);
		}

		inline void update(const Timer& timer) {
			scene->update(timer);
			audioWorld->update();
		}
	};
}
