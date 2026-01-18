#pragma once

#include "DxUIFeature.h"

#include "core/application/Application.h"
#include "core/feature/FeatureFactory.h"
#include "engine/directx/DxGraphicsFeature.h"

namespace Ghurund::UI::DirectX {
	class DxUIFeatureFactory:public FeatureFactory {
	public:
		DxUIFeatureFactory(Application& app):FeatureFactory(app) {}

		virtual OwnedNotNull<Feature> make() const override {
			auto graphicsFeature = app.Features.get<DxGraphicsFeature>();
			auto& graphics = graphicsFeature->Graphics;
			auto& memoryManager = graphicsFeature->MemoryManager;
			return OwnedNotNull<Feature>(ghnew DxUIFeature(app.ResourceManager, graphics, memoryManager));
		}
	};
}