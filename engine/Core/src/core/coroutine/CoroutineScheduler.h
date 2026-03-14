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
		Bag<std::coroutine_handle<>> fixedUpdateAwaiters, updateAwaiters;
		
		Timer& timer;

		std::mutex mutex;
		CoroutineThreadPool& threadPool;

	public:
		CoroutineScheduler(
			CoroutineThreadPool& threadPool,
			Timer& timer
		):threadPool(threadPool), timer(timer) {
		}

		DelayAwaiter delay(float delay) {
			return { delay };
		}

		DelayedUpdateAwaiter delayedUpdate(float delay, bool useScaledTime = true) {
			auto resumeTime = (useScaledTime ? timer.ScaledTime : timer.Time) + delay;
			return { delayedUpdateAwaiters, resumeTime, useScaledTime };
		}

		UpdateAwaiter nextFixedUpdate() {
			return { fixedUpdateAwaiters };
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

		void fixedUpdate();

		void update();
	};
}
