#pragma once

#include "Graphics.h"
#include "core/feature/FeatureFactory.h"

namespace Ghurund::Core::DirectX {
	class GraphicsFactory:public FeatureFactory {
	public:
		GraphicsFactory(FeatureProvider& features):FeatureFactory(features) {}

		virtual std::unique_ptr<Feature> make() const override {
			return std::unique_ptr<Feature>(ghnew Graphics());
		}
	};
}