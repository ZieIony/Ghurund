#pragma once

#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"
#include "ImGuiFeature.h"
#include "engine/directx/DxGraphicsFeature.h"

namespace Ghurund::Engine::DirectX {
	class ImGuiFeatureFactory:public FeatureFactory {
	public:
		ImGuiFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			auto graphics = app.Features.get<DxGraphicsFeature>();
			return OwnedNotNull<Feature>(ghnew ImGuiFeature(graphics->Graphics));
		}
	};
}
