#pragma once

#include "engine/2d/IGraphics2DContext.h"

namespace UnitTest {
	using namespace Ghurund::Engine;
	using namespace Ghurund::Engine::_2D;

	class Test2DContext:public IGraphics2DContext {
	public:
		virtual Mesh* makeSpriteMesh() override {
			throw NotImplementedException();
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeSpriteMaterial() override {
			throw NotImplementedException();
		}

		virtual Mesh* makeTileMapMesh(IntSize tileMapSize, Array<TileInfo>& tiles) override {
			throw NotImplementedException();
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeTileMapMaterial() override {
			throw NotImplementedException();
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeBoxVisualizationMaterial() override {
			throw NotImplementedException();
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeCapsuleVisualizationMaterial() override {
			throw NotImplementedException();
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeSegmentVisualizationMaterial() override {
			throw NotImplementedException();
		}
	};
}
