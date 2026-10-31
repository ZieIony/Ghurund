#pragma once

#include <entt.hpp>

namespace Ghurund::Engine {
	class Entity {
	private:
		entt::registry* registry;
		entt::entity id;

	public:
		Entity():registry(nullptr), id((entt::entity)0) {}

		Entity(entt::registry& registry, entt::entity id):registry(&registry), id(id) {}

		inline entt::entity getId() const {
			return id;
		}

		__declspec(property(get = getId)) entt::entity Id;

		template<typename T>
		inline bool hasComponent() {
			return registry->any_of<T>(id);
		}

		template<typename T>
		inline T& addComponent() {
			_ASSERTE(!hasComponent<T>());
			return registry->emplace<T>(id);
		}

		template<typename T>
		inline T& getComponent() {
			_ASSERTE(hasComponent<T>());
			return registry->get<T>(id);
		}

		template<typename T>
		inline void removeComponent() {
			_ASSERTE(hasComponent<T>());
			registry->remove<T>(id);
		}
	};
}
