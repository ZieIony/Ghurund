#pragma once

#include "Graphics2D.h"
#include "UIFeature.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::UI::Direct2D {
	class UIFeatureFactory:public FeatureFactory {
	public:
		UIFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual std::unique_ptr<Feature> make() const override {
			auto& graphics = app.Features.get<Ghurund::UI::Direct2D::Graphics2D>();
			return std::unique_ptr<Feature>(ghnew UIFeature(graphics, app.ResourceManager));
		}
	};
}