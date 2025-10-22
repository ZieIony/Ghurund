#pragma once

#include "GameAction.h"
#include "core/object/IntrusivePointer.h"

#include <cstdint>

namespace Ghurund::Engine {
	class BaseDispatchInputTask {
	public:
		uint8_t priority;

		BaseDispatchInputTask(uint8_t priority):priority(priority) {}

		virtual ~BaseDispatchInputTask() {}

		virtual BaseGameAction* getAction() = 0;

		__declspec(property(get = getAction)) BaseGameAction* Action;

		virtual void cancel() = 0;

		virtual void execute() = 0;
	};
}
