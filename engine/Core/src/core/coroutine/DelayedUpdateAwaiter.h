#pragma once

#include "core/collection/Bag.h"

#include <coroutine>

namespace Ghurund::Core {
	class DelayedUpdateAwaiter {
	private:
		Bag<DelayedUpdateAwaiter>& delayedUpdateAwaiters;
		std::coroutine_handle<> handle;
		uint64_t resumeTime;

	public:
		DelayedUpdateAwaiter(
			Bag<DelayedUpdateAwaiter>& delayedUpdateAwaiters,
			uint64_t resumeTime
		):delayedUpdateAwaiters(delayedUpdateAwaiters), resumeTime(resumeTime) {
		}

		DelayedUpdateAwaiter(
			const DelayedUpdateAwaiter& other
		):delayedUpdateAwaiters(other.delayedUpdateAwaiters), handle(other.handle), resumeTime(other.resumeTime) {
		}

		bool await_ready() const {
			return false;
		}

		bool await_suspend(std::coroutine_handle<> handle) {
			this->handle = handle;
			delayedUpdateAwaiters.add(*this);
			return true;
		}

		void await_resume() const {}

		DelayedUpdateAwaiter& operator=(const DelayedUpdateAwaiter& other) {
			if (this == &other)
				return *this;
			delayedUpdateAwaiters = other.delayedUpdateAwaiters;
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
	};
}
