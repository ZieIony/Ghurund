#pragma once

#include "engine/graphics/material/Material.h"
#include "core/coroutine/CoroutineTask.h"

namespace Ghurund::Engine::_3D {
	using namespace Ghurund::Core;

	class IGraphics3DContext {
	public:
		virtual CoroutineTask<IntrusivePointer<Material>> makeBoxVisualizationMaterial() = 0;

		virtual CoroutineTask<IntrusivePointer<Material>> makeCapsuleVisualizationMaterial() = 0;

		virtual CoroutineTask<IntrusivePointer<Material>> makeSegmentVisualizationMaterial() = 0;
	};
}
