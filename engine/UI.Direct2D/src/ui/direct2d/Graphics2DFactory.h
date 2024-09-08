#pragma once

#include "Graphics2D.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"
#include "engine/directx/Graphics.h"

namespace Ghurund::UI::Direct2D {
	class Graphics2DFactory:public FeatureFactory {
	public:
		Graphics2DFactory(Application& app):FeatureFactory(app) {}

		virtual std::unique_ptr<Feature> make() const override {
			auto& graphics = app.Features.get<Ghurund::Engine::DirectX::Graphics>();
			return std::unique_ptr<Feature>(ghnew Graphics2D(graphics));
		}
	};
}