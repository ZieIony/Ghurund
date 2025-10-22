#pragma once

#include "BaseInputDispatcher.h"
#include "DispatchInputTask.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<typename T>
	class InputDispatcher:public BaseInputDispatcher<T> {
	public:
		InputDispatcher(GameAction<T>* action, uint8_t priority)
			:BaseInputDispatcher<T>(IntrusivePointer<BaseGameAction>((BaseGameAction*)action), priority) {
			action->addReference();
		}

		virtual OwnedNotNull<BaseDispatchInputTask> makeDispatchEventTask(T value, uint64_t time) override {
			BaseInputDispatcher<T>::action->addReference();
			return OwnedNotNull<BaseDispatchInputTask>(ghnew DispatchInputTask<T>(
				BaseInputDispatcher<T>::priority,
				value,
				time,
				IntrusivePointer<GameAction<T>>((GameAction<T>*)BaseInputDispatcher<T>::action.get())
			));
		}
	};
}