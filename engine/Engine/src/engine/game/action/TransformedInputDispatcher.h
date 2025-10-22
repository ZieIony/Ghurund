#pragma once

#include "InputDispatcher.h"

namespace Ghurund::Engine {
	template<typename From, typename To, typename T>
	class TransformedInputDispatcher:public BaseInputDispatcher<From> {
	private:
		T transformer;

	public:
		TransformedInputDispatcher(
			GameAction<To>* action,
			T transformer,
			uint8_t priority
		):BaseInputDispatcher<From>(IntrusivePointer<BaseGameAction>((BaseGameAction*)action), priority), transformer(transformer) {
			action->addReference();
		}

		virtual OwnedNotNull<BaseDispatchInputTask> makeDispatchEventTask(From value, uint64_t time) override {
			BaseInputDispatcher<From>::action->addReference();
			return OwnedNotNull<BaseDispatchInputTask>(ghnew DispatchInputTask<To>(
				BaseInputDispatcher<From>::priority,
				transformer(value),
				time,
				IntrusivePointer<GameAction<To>>((GameAction<To>*)BaseInputDispatcher<From>::action.get())
			));
		}
	};
}