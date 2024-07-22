#pragma once

#include "Feature.h"
#include "core/Factory.h"

namespace Ghurund::Core {
	class Application;

	class FeatureFactory:public Factory<Feature> {
	protected:
		Application& app;

	public:
		FeatureFactory(Application& app):app(app) {}
	};
}