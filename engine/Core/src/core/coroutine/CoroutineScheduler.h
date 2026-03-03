#pragma once

#include "DelayAwaiter.h"
#include "UpdateAwaiter.h"

#include "core/collection/Bag.h"
#include "core/collection/List.h"
#include "core/Timer.h"

namespace Ghurund::Core {
	class CoroutineScheduler {
	private:
		Bag<DelayAwaiter> delayAwaiters;
		List<UpdateAwaiter> updateAwaiters;
		Timer& timer;

	public:
		CoroutineScheduler(Timer& timer):timer(timer) {}

		DelayAwaiter delay(uint64_t delayMs) {
			return DelayAwaiter(delayAwaiters, timer.TimeMs + delayMs);
		}

		UpdateAwaiter nextUpdate() {
			return UpdateAwaiter(updateAwaiters);
		}

		void update();
	};
}
