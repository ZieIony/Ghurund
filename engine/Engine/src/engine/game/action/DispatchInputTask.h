#pragma once

#include "BaseDispatchInputTask.h"

namespace Ghurund::Engine {
	template<typename T>
	class DispatchInputTask:public BaseDispatchInputTask {
	public:
		T value;
		uint64_t time;
		IntrusivePointer<GameAction<T>> gameAction;

		DispatchInputTask(
			uint8_t priority,
			T value,
			uint64_t time,
			IntrusivePointer<GameAction<T>> gameAction
		):BaseDispatchInputTask(priority), value(value), time(time), gameAction(gameAction) {
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
