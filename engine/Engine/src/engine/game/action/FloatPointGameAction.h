#pragma once

#include "GameAction.h"
#include <core/math/Point.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<>
	class GameAction<FloatPoint>:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<GameAction<FloatPoint>>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = GameAction<FloatPoint>::GET_TYPE();
#pragma endregion

	private:
		float threshold;

	public:
		GameAction(float threshold = 0.01):threshold(threshold) {}

		inline float getThreshold() const {
			return threshold;
		}

		__declspec(property(get = getThreshold)) float Threshold;

		virtual void onStarted(FloatPoint value) {}

		virtual void onInProgress(FloatPoint value, uint64_t duration) {}

		virtual void onFinished(FloatPoint value, uint64_t duration) {}
	};
}