#pragma once

#include "engine/ecs/ComponentLoader.h"

namespace Ghurund::Engine::_3D {

	class TransformComponent3DLoader:public ComponentLoader {
	public:
		virtual const WString& getComponentName() const override {
			static WString name = L"TransformComponent3D";
			return name;
		}

		virtual void loadComponent(
			NotNull<Scene> scene,
			NotNull<Entity> entity,
			const XMLElement& xml,
			const DirectoryPath& workingDir
		) override;
	};
}
