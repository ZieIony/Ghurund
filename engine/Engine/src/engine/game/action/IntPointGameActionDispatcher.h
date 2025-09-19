#pragma once

#include "GameActionDispatcher.h"
#include <core/math/Point.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<>
	class GameActionDispatcher<IntPoint> {
	protected:
		GameAction<IntPoint>* action;
		uint64_t startTime;
		IntPoint value;

	public:
		GameActionDispatcher(GameAction<IntPoint>* action, IntPoint initialValue = {}):action(action), value(initialValue) {}

		virtual ~GameActionDispatcher() {
			if (action)
				action->release();
		}

		virtual void dispatchEvent(IntPoint value, uint64_t time) {
			float currentLength = sqrtf(pow(this->value.x, 2) + pow(this->value.y, 2));
			float newLength = sqrtf(pow(value.x, 2) + pow(value.y, 2));
			if (currentLength == 0 && newLength > 0) {
				this->value = value;
				this->startTime = time;
				action->onStarted(value);
			} else if (currentLength > 0) {
				this->value = value;
				if (newLength > 0) {
					action->onInProgress(value, time - startTime);
				} else {
					action->onFinished(value, time - startTime);
				}
			}
		}
	};
}