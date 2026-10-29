#pragma once

#include "engine/application/GameApplication.h"
#include "Entity.h"

#include <entt.hpp>

namespace Ghurund::Engine {
	class World:public Initializable, public Noncopyable {
	private:
		friend class Entity;

	protected:
		virtual void onInit() override {

		}

		inline void uninitWorld() {
			entityRegistry.clear();
		}

		virtual void onDeinit() override {

		}

	public:
		entt::registry entityRegistry;	// TODO: fix getView<>() and make entityRegistry private
		GameApplication& app;

		World(
			GameApplication& app
		):app(app) {
		}

		~World() {
			if (IsInitialized)
				uninitWorld();
		}

		template<Derived<Entity> T>
		inline T spawnEntity() {
			return T(entityRegistry, entityRegistry.create());
		}

		inline void destroyEntity(Entity& entity) {
			entityRegistry.destroy(entity.Id);
		}

		// TODO: why this doesn't work?
		template<typename... T>
		[[nodiscard]]
		inline auto getView() const {
			return entityRegistry.view<T...>();
		}
	};
}
