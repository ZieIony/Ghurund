#pragma once

#include "Thread.h"
#include "Task.h"
#include "Waitable.h"
#include "core/collection/Queue.h"

#include <mutex>

namespace Ghurund::Core {
	class WorkerThread:public Thread {
	private:
		Queue<SharedPointer<Task>> queue;
		mutable std::mutex mutex;
		Waitable waitable;
		std::atomic_flag busy, running, finishing;

	public:
		Event<WorkerThread, void, bool> runningChanged = *this;
		Event<WorkerThread, void, bool> busyChanged = *this;

		virtual ~WorkerThread() {
			if (running.test() && !finishing.test())
				finish();
		}

		virtual void finish() override {
			finishing.test_and_set();
			waitable.notify();
			__super::finish();
		}

		inline void post(SharedPointer<Task> task) {
			std::unique_lock lock(mutex);
			queue.add(task);
			waitable.notify();
		}

		inline Queue<SharedPointer<Task>> getTasks() const {
			std::unique_lock lock(mutex);
			Queue<SharedPointer<Task>> copy = queue;
			return queue;
		}

		__declspec(property(get = getTasks)) Queue<SharedPointer<Task>> Tasks;

		virtual void run() override;

		inline bool isRunning() const {
			return running.test();
		}

		__declspec(property(get = isRunning)) bool Running;

		inline bool isBusy() const {
			return busy.test();
		}

		__declspec(property(get = isBusy)) bool Busy;
	};
}