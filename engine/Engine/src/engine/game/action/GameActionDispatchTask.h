#pragma once

#include "BaseGameActionDispatchEventTask.h"

namespace Ghurund::Engine {
	template<typename T>
	class GameActionDispatchEventTask:public BaseGameActionDispatchEventTask {
	public:
		T value;
		uint64_t time;
		IntrusivePointer<GameAction<T>> gameAction;

		GameActionDispatchEventTask(
			uint8_t priority,
			T value,
			uint64_t time,
			IntrusivePointer<GameAction<T>> gameAction
		):BaseGameActionDispatchEventTask(priority), value(value), time(time), gameAction(gameAction) {
		}

		virtual BaseGameAction* getAction() override {
			return gameAction.get();
		}

		virtual void cancel() override {
			gameAction->cancel();
		}

		virtual void execute() override {
			gameAction->dispatchEvent(value, time);
		}
	};
}
