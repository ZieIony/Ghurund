#pragma once

#include "GameAction.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<>
	class GameAction<float>:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<GameAction<float>>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = GameAction<float>::GET_TYPE();
#pragma endregion

	private:
		float threshold;
		float min, max;

	public:
		GameAction(float threshold = 0.01, float min = 0.0f, float max = 1.0f):
			threshold(threshold), min(min), max(max) {
		}

		inline float getThreshold() const {
			return threshold;
		}

		__declspec(property(get = getThreshold)) float Threshold;

		inline float getMin() const {
			return min;
		}

		__declspec(property(get = getMin)) float Min;

		inline float getMax() const {
			return max;
		}

		__declspec(property(get = getMax)) float Max;

		virtual void onStarted(float value) {}

		virtual void onInProgress(float value, uint64_t duration) {}

		virtual void onFinished(float value, uint64_t duration) {}
	};
}