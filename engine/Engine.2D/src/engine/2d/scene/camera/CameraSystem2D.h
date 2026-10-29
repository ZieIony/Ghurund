#pragma once

#include "CameraComponent2D.h"

#include "engine/ecs/System.h"
#include "engine/2d/World2D.h"
#include "engine/2d/scene/transform/TransformComponent2D.h"

namespace Ghurund::Engine::_2D {
	class CameraSystem2D:public System {
	private:
		World2D& world;

	public:
		CameraSystem2D(World2D& world):world(world) {}

		virtual void update(const Timer& timer) override {
			auto view = world.entityRegistry.view<TransformComponent2D, CameraComponent2D>();
			view.each([](const auto& id, const auto& transform, auto& camera) {
				camera.update(transform);
			});
		}
	};
}
