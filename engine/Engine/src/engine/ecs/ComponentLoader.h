#pragma once

#include <core/io/DirectoryPath.h>
#include <core/object/RefCountedObject.h>
#include <core/xml/XMLElement.h>
#include <engine/ecs/Entity.h>
#include <engine/ecs/Scene.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ComponentLoader:public RefCountedObject {
	public:
		virtual const WString& getComponentName() const = 0;

		virtual void loadComponent(
			NotNull<Scene> scene,
			NotNull<Entity> entity,
			const XMLElement& xml,
			const DirectoryPath& workingDir
		) = 0;
	};
}
