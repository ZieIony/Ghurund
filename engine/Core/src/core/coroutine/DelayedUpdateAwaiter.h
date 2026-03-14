#pragma once

#include "core/collection/Bag.h"

#include <coroutine>

namespace Ghurund::Core {
	class DelayedUpdateAwaiter {
	private:
		Bag<DelayedUpdateAwaiter>& delayedUpdateAwaiters;
		std::coroutine_handle<> handle;
		double resumeTime;
		bool useScaledTime;

	public:
		DelayedUpdateAwaiter(
			Bag<DelayedUpdateAwaiter>& delayedUpdateAwaiters,
			double resumeTime,
			bool useScaledTime
		):delayedUpdateAwaiters(delayedUpdateAwaiters), resumeTime(resumeTime), useScaledTime(useScaledTime) {
		}

		DelayedUpdateAwaiter(
			const DelayedUpdateAwaiter& other
		):delayedUpdateAwaiters(other.delayedUpdateAwaiters), handle(other.handle), resumeTime(other.resumeTime), useScaledTime(other.useScaledTime) {
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

		inline double getResumeTime() const {
			return resumeTime;
		}

		__declspec(property(get = getResumeTime)) double ResumeTime;

		inline bool getUseScaledTime() const {
			return useScaledTime;
		}

		__declspec(property(get = getUseScaledTime)) bool UseScaledTime;

		inline void resume() {
			handle.resume();
		}
	};
}
