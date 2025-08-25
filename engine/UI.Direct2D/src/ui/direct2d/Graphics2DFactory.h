#pragma once

#include "Graphics2D.h"
#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"
#include "engine/directx/DxGraphics.h"

namespace Ghurund::UI::Direct2D {
	class Graphics2DFactory:public FeatureFactory {
	public:
		Graphics2DFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			auto graphics = app->Features->get<Ghurund::Engine::DirectX::DxGraphics>();
			return OwnedNotNull<Feature>(ghnew Graphics2D(graphics));
		}
	};
}