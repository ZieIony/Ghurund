#pragma once

#include "engine/3d/graphics/camera/CameraComponent3D.h"
#include "engine/ecs/ComponentLoader.h"

namespace Ghurund::Engine::_3D {

	class CameraComponent3DLoader:public ComponentLoader {
	public:
		virtual const WString& getComponentName() const override {
			static WString name = L"CameraComponent3D";
			return name;
		}

		virtual void loadComponent(
			NotNull<Scene> scene,
			NotNull<Entity> entity,
			const XMLElement& xml,
			const DirectoryPath& workingDir
		) override {
			auto& cameraComponent = entity->addComponent<CameraComponent3D>();
			scene->Camera = cameraComponent.Camera;
		}
	};
}
