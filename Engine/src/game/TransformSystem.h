#pragma once

#include "ecs/System.h"
#include "TransformComponent.h"

namespace Ghurund {
	class TransformSystem :public System<TransformComponent> {
	public:
		TransformComponent* makeComponent() {
			TransformComponent* component = ghnew TransformComponent();
			Components.add(component);
			return component;
		}

		void update(float dt) {
			for (TransformComponent* c : Components)
				c->update();
		}
	};
}