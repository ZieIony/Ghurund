#pragma once

#include "GameAction.h"
#include "GameActionDispatcher.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<>
	class GameActionDispatcher<bool>:public BaseGameActionDispatcher<bool> {
	protected:
		GameAction<bool>* action;
		uint64_t startTime;
		bool value;

	public:
		GameActionDispatcher(GameAction<bool>* action, bool initialValue = {}):action(action), value(initialValue) {}

		virtual ~GameActionDispatcher() {
			if (action)
				action->release();
		}

		virtual void dispatchEvent(bool value, uint64_t time) {
			if (!this->value && value) {
				this->value = value;
				this->startTime = time;
				action->onStarted(value);
			} else if (this->value) {
				this->value = value;
				if (value) {
					action->onInProgress(value, time - startTime);
				} else {
					action->onFinished(value, time - startTime);
				}
			}
		}
	};
}