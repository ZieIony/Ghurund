#pragma once

#include "GameActionDispatcher.h"

namespace Ghurund::Engine {
	template<typename From, typename To, typename T>
	class TransformedGameActionDispatcher:public BaseGameActionDispatcher<From> {
	private:
		T transformer;

	public:
		TransformedGameActionDispatcher(
			GameAction<To>* action,
			T transformer,
			uint8_t priority
		):BaseGameActionDispatcher<From>(IntrusivePointer<BaseGameAction>((BaseGameAction*)action), priority), transformer(transformer) {
			action->addReference();
		}

		virtual OwnedNotNull<BaseGameActionDispatchEventTask> makeDispatchEventTask(From value, uint64_t time) override {
			BaseGameActionDispatcher<From>::action->addReference();
			return OwnedNotNull<BaseGameActionDispatchEventTask>(ghnew GameActionDispatchEventTask<To>(
				BaseGameActionDispatcher<From>::priority,
				transformer(value),
				time,
				IntrusivePointer<GameAction<To>>((GameAction<To>*)BaseGameActionDispatcher<From>::action.get())
			));
		}
	};
}