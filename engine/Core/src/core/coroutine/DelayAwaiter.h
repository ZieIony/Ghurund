#pragma once

#include <coroutine>

namespace Ghurund::Core {
	class DelayAwaiter {
	private:
		std::coroutine_handle<> handle;
		uint64_t delay;

	public:
		DelayAwaiter(uint64_t delay):delay(delay) {}

		//DelayAwaiter(const DelayAwaiter& other):handle(other.handle), delay(other.delay) {}

		bool await_ready() const {
			return false;
		}

		void await_suspend(std::coroutine_handle<> handle) {
			std::thread([=]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
				handle.resume();
			}).detach();
		}

		void await_resume() const {}
	};
}
