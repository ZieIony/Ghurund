#pragma once

#include "DispatchInputTask.h"
#include "core/object/OwnedNotNull.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<typename T>
	class BaseInputDispatcher {
	protected:
		uint8_t priority;
		IntrusivePointer<BaseGameAction> action;

	public:
		BaseInputDispatcher(IntrusivePointer<BaseGameAction> action, uint8_t priority):action(action), priority(priority) {}

		virtual ~BaseInputDispatcher() {
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

		virtual OwnedNotNull<BaseDispatchInputTask> makeDispatchEventTask(T value, uint64_t time) = 0;
	};
}