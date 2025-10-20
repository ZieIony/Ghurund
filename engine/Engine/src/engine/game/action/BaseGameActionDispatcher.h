#pragma once

#include "GameActionDispatchTask.h"
#include "core/object/OwnedNotNull.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<typename T>
	class BaseGameActionDispatcher {
	protected:
		uint8_t priority;
		IntrusivePointer<BaseGameAction> action;

	public:
		BaseGameActionDispatcher(IntrusivePointer<BaseGameAction> action, uint8_t priority):action(action), priority(priority) {}

		virtual ~BaseGameActionDispatcher() {
			action->cancel();
		}

		BaseGameAction* getAction() {
			return action.get();
		}

		__declspec(property(get = getAction)) BaseGameAction* Action;

		uint8_t getPriority() const {
			return priority;
		}

		__declspec(property(get = getPriority)) uint8_t Priority;

		inline void cancelAction() {
			action->cancel();
		}

		virtual OwnedNotNull<BaseGameActionDispatchEventTask> makeDispatchEventTask(T value, uint64_t time) = 0;
	};
}