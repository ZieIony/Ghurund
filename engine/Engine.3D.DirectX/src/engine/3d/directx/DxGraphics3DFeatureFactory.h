#pragma once

#include "DxGraphics3DFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::Engine::_3D::DirectX {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine::DirectX;

	class DxGraphics3DFeatureFactory:public FeatureFactory {
	public:
		DxGraphics3DFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			return OwnedNotNull<Feature>(ghnew DxGraphics3DFeature(app.ResourceManager));
		}
	};
}
