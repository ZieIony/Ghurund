#pragma once

#include "DxGraphicsFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::Engine::DirectX {
	class DxGraphicsFeatureFactory:public FeatureFactory {
	public:
		DxGraphicsFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			return OwnedNotNull<Feature>(ghnew DxGraphicsFeature(app.ResourceManager));
		}
	};
}