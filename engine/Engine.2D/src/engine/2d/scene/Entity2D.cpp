#include "ghe2dpch.h"
#include "Entity2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& Entity2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Entity2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
	
	void Entity2D::fixedUpdate(const Timer& timer) {
		transformComponent->fixedUpdate(timer);
		for (auto& component : components)
			component->fixedUpdate(timer);
	}
	
	void Entity2D::update(const Timer& timer) {
		transformComponent->update(timer);
		for (auto& component : components)
			component->update(timer);
	}
	
	void Entity2D::draw(RenderGroup& group) {
		for (auto& component : components)
			component->draw(group);
	}
}
