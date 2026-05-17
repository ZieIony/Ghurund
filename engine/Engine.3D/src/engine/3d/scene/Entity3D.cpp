#include "ghe3dpch.h"
#include "Entity3D.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& Entity3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Entity3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
	
	void Entity3D::fixedUpdate(const Timer& timer) {
		transformComponent->fixedUpdate(timer);
		for (auto& component : components)
			component->fixedUpdate(timer);
	}
	
	void Entity3D::update(const Timer& timer) {
		transformComponent->update(timer);
		for (auto& component : components)
			component->update(timer);
	}
	
	void Entity3D::draw(RenderGroup& group) {
		for (auto& component : components)
			component->draw(group);
	}
}
