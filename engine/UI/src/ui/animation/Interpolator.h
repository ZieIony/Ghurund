#pragma once

#include <cmath>
#include <DirectXMath.h>

namespace Ghurund::UI {
	class Interpolator {
	public:
		virtual ~Interpolator() = 0 {};

		virtual float getProgress(float progress) const = 0;
	};

	class LinearInterpolator:public Interpolator {
	public:
		virtual float getProgress(float progress) const override {
			return progress;
		}
	};

	class CosInterpolator:public Interpolator {
	public:
		virtual float getProgress(float progress) const override {
			return (float)(cos((progress + 1) * ::DirectX::XM_PI) / 2.0f) + 0.5f;
		}
	};
}
