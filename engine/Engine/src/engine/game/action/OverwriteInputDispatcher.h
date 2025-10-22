#pragma once

#include "InputDispatcher.h"

namespace Ghurund::Engine {
	template<typename From, typename To>
	class OverwriteInputDispatcher:public BaseInputDispatcher<From> {
	private:
		To value;

	public:
		OverwriteInputDispatcher(
			GameAction<To>* action,
			const To& value,
			uint8_t priority
		):BaseInputDispatcher<From>(IntrusivePointer<BaseGameAction>((BaseGameAction*)action), priority), value(value) {
			action->addReference();
		}

		virtual OwnedNotNull<BaseDispatchInputTask> makeDispatchEventTask(From value, uint64_t time) override {
			BaseInputDispatcher<From>::action->addReference();
			return OwnedNotNull<BaseDispatchInputTask>(ghnew DispatchInputTask<To>(
				BaseInputDispatcher<From>::priority,
				this->value,
				time,
				IntrusivePointer<GameAction<To>>((GameAction<To>*)BaseInputDispatcher<From>::action.get())
			));
		}
	};
}