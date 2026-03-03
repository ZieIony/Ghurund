#include "ghcpch.h"
#include "CoroutineScheduler.h"

namespace Ghurund::Core {
	void CoroutineScheduler::update() {
		List<DelayAwaiter> delayAwaitersToResume;
		for (size_t i = 0; i < delayAwaiters.Size;) {
			auto& awaiter = delayAwaiters[i];
			if (awaiter.IsDone) {
				awaiter.destroy();
				delayAwaiters.removeAt(i);
			} else if (awaiter.ResumeTime <= timer.TimeMs) {
				delayAwaitersToResume.add(awaiter);
				delayAwaiters.removeAt(i);
			} else {
				i++;
			}
		}
		for (auto& awaiter : delayAwaitersToResume)
			awaiter.resume();

		List<UpdateAwaiter> updateAwaitersToResume = updateAwaiters;
		updateAwaiters.clear();
		for (auto& awaiter : updateAwaitersToResume) {
			if (awaiter.IsDone) {
				awaiter.destroy();
			} else {
				awaiter.resume();
			}
		}
	}
}
