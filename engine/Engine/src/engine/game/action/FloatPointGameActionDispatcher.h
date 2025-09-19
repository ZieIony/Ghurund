#pragma once

#include "FloatPointGameAction.h"
#include <core/math/Point.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<>
	class GameActionDispatcher<FloatPoint>:public BaseGameActionDispatcher<FloatPoint> {
	protected:
		GameAction<FloatPoint>* action;
		uint64_t startTime;
		FloatPoint value;

	public:
		GameActionDispatcher(GameAction<FloatPoint>* action, FloatPoint initialValue = {}):action(action), value(initialValue) {}

		virtual ~GameActionDispatcher() {
			if (action)
				action->release();
		}

		virtual void dispatchEvent(FloatPoint value, uint64_t time) {
			float currentLength = sqrtf(pow(this->value.x, 2) + pow(this->value.y, 2));
			float newLength = sqrtf(pow(value.x, 2) + pow(value.y, 2));
			if (currentLength < action->Threshold && newLength >= action->Threshold) {
				this->value = value;
				this->startTime = time;
				action->onStarted(value);
			} else if (currentLength >= action->Threshold) {
				this->value = value;
				if (newLength >= action->Threshold) {
					action->onInProgress(value, time - startTime);
				} else {
					action->onFinished(value, time - startTime);
				}
			}
		}
	};
}