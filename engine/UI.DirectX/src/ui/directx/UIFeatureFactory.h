#pragma once

#include "DxUIFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::UI::DirectX {
	class UIFeatureFactory:public FeatureFactory {
	public:
		UIFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			return OwnedNotNull<Feature>(ghnew DxUIFeature(app->ResourceManager));
		}
	};
}