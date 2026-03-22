#pragma once

#include "AudioFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class AudioFeatureFactory:public FeatureFactory {
	public:
		AudioFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			return OwnedNotNull<Feature>(ghnew AudioFeature(app.ResourceManager));
		}
	};
}
