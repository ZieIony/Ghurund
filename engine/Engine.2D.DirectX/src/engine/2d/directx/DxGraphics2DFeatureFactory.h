#pragma once

#include "DxGraphics2DFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"
#include "engine/directx/DxGraphicsFeature.h"

namespace Ghurund::Engine::_2D::DirectX {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine::DirectX;

	class DxGraphics2DFeatureFactory:public FeatureFactory {
	public:
		DxGraphics2DFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			auto graphicsFeature = app.Features.get<DxGraphicsFeature>();
			return OwnedNotNull<Feature>(ghnew DxGraphics2DFeature(app.ResourceManager, graphicsFeature->MemoryManager));
		}
	};
}
