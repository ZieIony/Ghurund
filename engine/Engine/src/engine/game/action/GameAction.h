#pragma once

#include "BaseGameAction.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	template<typename T>
	class GameAction:public BaseTypedGameAction<T> {
	};

	template<>
	class GameAction<bool>:public BaseTypedGameAction<bool> {
	protected:
		virtual bool getShouldBeInProgress(const bool& value) const override {
			return value;
		}
	};

	template<>
	class GameAction<float>:public BaseTypedGameAction<float> {
	private:
		float threshold;

	protected:
		virtual bool getShouldBeInProgress(const float& value) const override {
			return value >= threshold;
		}

	public:
		GameAction(float threshold = 0.01):
			threshold(std::max(0.0f, std::min(threshold, 1.0f))) {
		}

		inline float getThreshold() const {
			return threshold;
		}

		__declspec(property(get = getThreshold)) float Threshold;

		virtual void dispatchEvent(float value, uint64_t time) override {
			__super::dispatchEvent((value - threshold) / (1 - threshold), time);
		}
	};

	template<>
	class GameAction<XMFLOAT2>:public BaseTypedGameAction<XMFLOAT2> {
	private:
		float threshold;

	protected:
		virtual bool getShouldBeInProgress(const XMFLOAT2& value) const override {
			return sqrtf(powf(value.x, 2) + powf(value.y, 2)) >= threshold;
		}

	public:
		GameAction(float threshold = 0.01):threshold(std::max(0.0f, std::min(threshold, 1.0f))) {}

		inline float getThreshold() const {
			return threshold;
		}

		__declspec(property(get = getThreshold)) float Threshold;

		/*virtual void dispatchEvent(FloatPoint value, uint64_t time) override {
			__super::dispatchEvent((value - threshold) / (1 - threshold), time);
		}*/
	};

	template<>
	class GameAction<XMINT2>:public BaseTypedGameAction<XMINT2> {
	private:
		float threshold;

	protected:
		virtual bool getShouldBeInProgress(const XMINT2& value) const override {
			return sqrtf((float)(pow(value.x, 2) + pow(value.y, 2))) >= threshold;
		}

	public:
		GameAction(float threshold = 0.01):threshold(std::max(0.0f, std::min(threshold, 1.0f))) {}

		inline float getThreshold() const {
			return threshold;
		}

		__declspec(property(get = getThreshold)) float Threshold;

		/*virtual void dispatchEvent(FloatPoint value, uint64_t time) override {
			__super::dispatchEvent((value - threshold) / (1 - threshold), time);
		}*/
	};
}