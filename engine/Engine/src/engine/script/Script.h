#pragma once

#include "core/object/NotNull.h"
#include "core/object/RefCountedObject.h"
#include "engine/ecs/Entity.h"
#include "engine/ecs/Scene.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class Script:public RefCountedObject {
	public:
		virtual void onInit(NotNull<Entity> owner, NotNull<Scene> scene) {}
	};
}
