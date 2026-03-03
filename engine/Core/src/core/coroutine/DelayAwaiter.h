#pragma once

#include "core/collection/Bag.h"

#include <coroutine>

namespace Ghurund::Core {
	class DelayAwaiter {
	private:
		Bag<DelayAwaiter>& delayAwaiters;
		std::coroutine_handle<> handle;
		uint64_t resumeTime;

	public:
		DelayAwaiter(Bag<DelayAwaiter>& delayAwaiters, uint64_t resumeTime):delayAwaiters(delayAwaiters), resumeTime(resumeTime) {}

		DelayAwaiter(const DelayAwaiter& other):delayAwaiters(other.delayAwaiters), handle(other.handle), resumeTime(other.resumeTime) {}

		bool await_ready() const {
			return false;
		}

		bool await_suspend(std::coroutine_handle<> handle) {
			this->handle = handle;
			delayAwaiters.add(*this);
			return true;
		}

		void await_resume() const {}

		DelayAwaiter& operator=(const DelayAwaiter& other) {
			if (this == &other)
				return *this;
			handle = other.handle;
			resumeTime = other.resumeTime;
			return *this;
		}

		inline uint64_t getResumeTime() const {
			return resumeTime;
		}

		__declspec(property(get = getResumeTime)) uint64_t ResumeTime;

		inline void resume() {
			handle.resume();
		}

		inline bool getIsDone() const {
			return handle.done();
		}

		__declspec(property(get = getIsDone)) bool IsDone;

		inline void destroy() {
			handle.destroy();
		}
	};
}
