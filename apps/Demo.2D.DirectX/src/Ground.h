#pragma once

#include "engine/2d/scene/Entity2D.h"
#include <engine/2d/physics/component/BoxComponent2D.h>
#include <engine/2d/physics/component/SegmentComponent2D.h>
#include <engine/2d/scene/tiles/TileMap.h>
#include <engine/2d/scene/tiles/TileMapComponent.h>

namespace Demo {
	using namespace Ghurund::Engine::_2D;

	class Ground:public Entity2D {
	private:
		IntrusivePointer<BoxComponent2D> groundBox;
		IntrusivePointer<SegmentComponent2D> segmentBox;
		IntrusivePointer<TileMapComponent> tileMapComponent;
		IntrusivePointer<TileMap> tileMap;

	protected:
		virtual CoroutineTask<void> onInit() override;

	public:
		Ground(World2D& world):Entity2D(world) {}
	};
}
