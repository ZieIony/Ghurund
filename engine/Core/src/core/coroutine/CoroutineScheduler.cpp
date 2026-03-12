#include "ghcpch.h"
#include "CoroutineScheduler.h"

namespace Ghurund::Core {
	void CoroutineScheduler::update() {
		{
			std::unique_lock<std::mutex> lock(mutex);
			updateAwaiters.addAll(fromAnotherThread);
			fromAnotherThread.clear();
		}

		List<DelayedUpdateAwaiter> delayAwaitersToResume;
		for (size_t i = 0; i < delayedUpdateAwaiters.Size;) {
			auto& awaiter = delayedUpdateAwaiters[i];
			if (awaiter.ResumeTime <= timer.TimeMs) {
				delayAwaitersToResume.add(awaiter);
				delayedUpdateAwaiters.removeAt(i);
			} else {
				i++;
			}
		}
		for (auto& awaiter : delayAwaitersToResume)
			awaiter.resume();

		List<std::coroutine_handle<>> updateAwaitersToResume = updateAwaiters;
		updateAwaiters.clear();
		for (auto& awaiter : updateAwaitersToResume)
			awaiter.resume();

		for (size_t i = 0; i < tasks.Size;) {
			auto& task = tasks[i];
			if (task.IsDone) {
				tasks.removeAt(i);
			} else {
				i++;
			}
		}
	}
}
