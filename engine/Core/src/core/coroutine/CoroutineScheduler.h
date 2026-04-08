#pragma once

#include "CoroutineTask.h"
#include "CoroutineThreadPool.h"
#include "DelayAwaiter.h"
#include "DelayedUpdateAwaiter.h"
#include "ThreadAwaiter.h"
#include "UpdateAwaiter.h"

#include "core/collection/Bag.h"
#include "core/Timer.h"

#include <mutex>

namespace Ghurund::Core {
	class CoroutineScheduler {
	private:
		Bag<CoroutineTask<void>> tasks;
		Bag<std::coroutine_handle<>> fromAnotherThread;
		Bag<DelayedUpdateAwaiter> delayedUpdateAwaiters;
		Bag<std::coroutine_handle<>> updateAwaiters;
		Timer& timer;
		std::mutex mutex;

		CoroutineThreadPool& threadPool;

	public:
		CoroutineScheduler(
			CoroutineThreadPool& threadPool,
			Timer& timer
		):threadPool(threadPool), timer(timer) {
		}

		DelayAwaiter delay(uint64_t delayMs) {
			return { delayMs };
		}

		DelayedUpdateAwaiter delayedUpdate(uint64_t delayMs) {
			return { delayedUpdateAwaiters, timer.TimeMs + delayMs };
		}

		UpdateAwaiter nextUpdate() {
			return { updateAwaiters };
		}

		ThreadAwaiter mainThread() {
			return { fromAnotherThread };
		}

		auto backgroundThread() {
			return threadPool.schedule();
		}

		inline void launch(CoroutineTask<void> task) {
			tasks.add(task);
			task.resume();
		}

		void update();
	};
}
