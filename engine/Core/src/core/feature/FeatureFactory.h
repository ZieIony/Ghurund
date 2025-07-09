#pragma once

#include "Feature.h"
#include "core/Factory.h"

namespace Ghurund::Core {
	class Application;

	class FeatureFactory:public Factory<Feature> {
	protected:
		// borrowed
		Application* app;

	public:
		FeatureFactory(NotNull<Application> app):app(&app) {}
	};
}