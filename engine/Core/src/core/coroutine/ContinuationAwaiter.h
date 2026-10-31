#pragma once

#include <coroutine>

namespace Ghurund::Core {
	template<typename promise_type>
	struct ContinuationAwaiter {
		std::coroutine_handle<promise_type> handle;

		bool await_ready() const noexcept { return !handle || handle.done(); }

		auto await_suspend(std::coroutine_handle<> calling) noexcept {
			handle.promise().continuation = calling;
			return handle;
		}

		decltype(auto) await_resume() {
			return handle.promise().getValue();
		}
	};
}
