#pragma once

#include "EngineFeature.h"

#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class EngineFeatureFactory:public FeatureFactory {
	public:
		EngineFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			return OwnedNotNull<Feature>(ghnew EngineFeature(app.ResourceManager));
		}
	};
}
