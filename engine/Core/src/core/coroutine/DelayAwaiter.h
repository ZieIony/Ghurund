#pragma once

#include <coroutine>

namespace Ghurund::Core {
	class DelayAwaiter {
	private:
		std::coroutine_handle<> handle;
		float delay;

	public:
		DelayAwaiter(float delay):delay(delay) {}

		//DelayAwaiter(const DelayAwaiter& other):handle(other.handle), delay(other.delay) {}

		bool await_ready() const {
			return false;
		}

		void await_suspend(std::coroutine_handle<> handle) {
			std::thread([=]() {
				std::this_thread::sleep_for(std::chrono::milliseconds((uint32_t)(delay * 1000)));
				handle.resume();
			}).detach();
		}

		void await_resume() const {}
	};
}
