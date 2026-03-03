#pragma once

#include "Graphics2DFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class Graphics2DFeatureFactory:public FeatureFactory {
	public:
		Graphics2DFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			return OwnedNotNull<Feature>(ghnew Graphics2DFeature(app.ResourceManager));
		}
	};
}
