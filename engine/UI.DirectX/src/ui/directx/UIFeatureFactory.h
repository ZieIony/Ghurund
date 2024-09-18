#pragma once

#include "UIFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::UI::DirectX {
	class UIFeatureFactory:public FeatureFactory {
	public:
		UIFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual std::unique_ptr<Feature> make() const override {
			return std::unique_ptr<Feature>(ghnew UIFeature(app.ResourceManager));
		}
	};
}