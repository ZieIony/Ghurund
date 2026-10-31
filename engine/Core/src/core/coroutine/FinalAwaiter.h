#pragma once

#include <coroutine>

namespace Ghurund::Core {
	template<typename promise_type>
	struct FinalAwaiter {
		bool await_ready() const noexcept { return false; }

		auto await_suspend(std::coroutine_handle<promise_type> handle) noexcept {
			return handle.promise().continuation;
		}

		void await_resume() const noexcept {}
	};
}
