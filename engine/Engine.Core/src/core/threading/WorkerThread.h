#pragma once

#include "ConcurrentTaskQueue.h"
#include "Thread.h"
#include "Task.h"
#include "core/Pointer.h"
#include "Waitable.h"
#include "core/collection/List.h"
#include "core/string/String.h"

namespace Ghurund::Core {
	class WorkerThread:public Thread {
	private:
		Queue<SharedPointer<Task>> queue;
		mutable CriticalSection section;
		Waitable waitable;
		std::atomic_flag busy, running, finishing;

	public:
		Event<WorkerThread, bool> runningChanged = *this;
		Event<WorkerThread, bool> busyChanged = *this;

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
			SectionLock lock(section);
			queue.add(task);
			waitable.notify();
		}

		inline Queue<SharedPointer<Task>> getTasks() const {
			SectionLock lock(section);
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