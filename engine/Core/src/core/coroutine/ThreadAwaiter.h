#pragma once

#include "core/collection/Bag.h"

#include <coroutine>

namespace Ghurund::Core {
	class ThreadAwaiter {
	private:
		Bag<std::coroutine_handle<>>& threadAwaiters;

	public:
		ThreadAwaiter(Bag<std::coroutine_handle<>>& threadAwaiters):threadAwaiters(threadAwaiters) {}

		ThreadAwaiter(const ThreadAwaiter& other):threadAwaiters(other.threadAwaiters) {}

		bool await_ready() const {
			return false;
		}

		bool await_suspend(std::coroutine_handle<> handle) {
			threadAwaiters.add(handle);
			return true;
		}

		void await_resume() const {}
	};
}
