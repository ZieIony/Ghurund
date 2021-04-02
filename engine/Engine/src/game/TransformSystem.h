#pragma once

#include "ecs/System.h"
#include "TransformComponent.h"

namespace Ghurund {
	class TransformSystem :public System<TransformComponent> {
	public:
		void update(float dt) {
			for (TransformComponent* c : Components)
				c->update();
		}
	};
}