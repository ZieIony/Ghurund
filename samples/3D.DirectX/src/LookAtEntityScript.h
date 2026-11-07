#pragma once

#include "engine/script/Script.h"
#include "engine/ecs/Entity.h"
#include "engine/3d/graphics/mesh/MeshComponent.h"
#include "engine/3d/graphics/transform/TransformComponent3D.h"
#include "engine/3d/graphics/camera/CameraComponent3D.h"
#include "engine/ecs/NameComponent.h"

#include <DirectXCollision.h>

namespace Sample {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;
	using namespace Ghurund::Engine::_3D;
	using namespace ::DirectX;

	class LookAtEntityScript:public Script {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = LookAtEntityScript::GET_TYPE();
#pragma endregion

	private:
		inline void lookAt(Entity& entity, Camera3D& camera) {
			auto& transformComponent = entity.getComponent<TransformComponent3D>();
			auto& meshComponent = entity.getComponent<MeshComponent>();

			BoundingOrientedBox bob, transformedBob;
			BoundingOrientedBox::CreateFromBoundingBox(bob, meshComponent.Mesh->BoundingBox);
			transformComponent.update();
			auto transform = XMLoadFloat4x4(&transformComponent.WorldTransformation);
			bob.Transform(transformedBob, transform);
			camera.setDirectionBoxUp({ -1, -0.2f, 1 }, transformedBob);
		}

	public:
		virtual void onInit(NotNull<Entity> owner, NotNull<Scene> scene) override {
			auto& cameraComponent = owner->getComponent<CameraComponent3D>();
		
			auto view = scene->entityRegistry.view<NameComponent>();
			for (auto [entityId, nameComponent] : view.each()) {
				if (nameComponent.name == L"helmet") {
					auto lookAtEntity = Entity(scene->entityRegistry, entityId);
					lookAt(lookAtEntity, *cameraComponent.Camera);
					return;
				}
			}
		}
	};
}
