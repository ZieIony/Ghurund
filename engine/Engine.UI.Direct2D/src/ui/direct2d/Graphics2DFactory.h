#pragma once

#include "Graphics2D.h"
#include "core/application/Application.h"
#include "core/directx/Graphics.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::UI::Direct2D {
	class Graphics2DFactory:public FeatureFactory {
	public:
		Graphics2DFactory(Application& app):FeatureFactory(app) {}

		virtual std::unique_ptr<Feature> make() const override {
			auto& graphics = app.Features.get<Ghurund::Core::DirectX::Graphics>();
			return std::unique_ptr<Feature>(ghnew Graphics2D(graphics));
		}
	};
}