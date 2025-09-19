#pragma once

#include "FloatGameAction.h"
#include "GameActionDispatcher.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<>
	class GameActionDispatcher<float>:public BaseGameActionDispatcher<float> {
	protected:
		GameAction<float>* action;
		uint64_t startTime;
		float value;

	public:
		GameActionDispatcher(GameAction<float>* action, float initialValue = {}):action(action), value(initialValue) {}

		virtual ~GameActionDispatcher() {
			if (action)
				action->release();
		}

		virtual void dispatchEvent(float value, uint64_t time) {
			if (this->value < action->Threshold && value >= action->Threshold) {
				this->value = value;
				this->startTime = time;
				action->onStarted(value);
			} else if (this->value >= action->Threshold) {
				this->value = value;
				if (value >= action->Threshold) {
					action->onInProgress(value, time - startTime);
				} else {
					action->onFinished(value, time - startTime);
				}
			}
		}
	};
}