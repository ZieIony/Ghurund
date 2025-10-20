#pragma once

#include "BaseGameActionDispatcher.h"
#include "GameActionDispatchTask.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<typename T>
	class GameActionDispatcher:public BaseGameActionDispatcher<T> {
	public:
		GameActionDispatcher(GameAction<T>* action, uint8_t priority)
			:BaseGameActionDispatcher<T>(IntrusivePointer<BaseGameAction>((BaseGameAction*)action), priority) {
			action->addReference();
		}

		virtual OwnedNotNull<BaseGameActionDispatchEventTask> makeDispatchEventTask(T value, uint64_t time) override {
			BaseGameActionDispatcher<T>::action->addReference();
			return OwnedNotNull<BaseGameActionDispatchEventTask>(ghnew GameActionDispatchEventTask<T>(
				BaseGameActionDispatcher<T>::priority,
				value,
				time,
				IntrusivePointer<GameAction<T>>((GameAction<T>*)BaseGameActionDispatcher<T>::action.get())
			));
		}
	};
}