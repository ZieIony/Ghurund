#pragma once

#include "GraphicsFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class GraphicsFeatureFactory:public FeatureFactory {
	public:
		GraphicsFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			return OwnedNotNull<Feature>(ghnew GraphicsFeature(app.ResourceManager));
		}
	};
}
