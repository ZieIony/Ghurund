#pragma once

#include <coroutine>
#include <exception>

namespace Ghurund::Core {
	class CoroutineTask {
	public:
		struct promise_type;

		using handle_type = std::coroutine_handle<promise_type>;

		struct promise_type {
			std::exception_ptr exception = nullptr;

			CoroutineTask get_return_object() {
				return CoroutineTask(handle_type::from_promise(*this));
			}

			std::suspend_never initial_suspend() noexcept {
				return {};
			}

			std::suspend_never final_suspend() noexcept {
				return {};
			}

			void return_void() {}

			void unhandled_exception() {
				exception = std::current_exception();
			}
		};

	private:
		handle_type handle;

		explicit CoroutineTask(handle_type handle): handle(handle) {}

		CoroutineTask(const CoroutineTask&) = delete;
		CoroutineTask& operator=(const CoroutineTask&) = delete;

	public:
		CoroutineTask(CoroutineTask&& other) noexcept: handle(other.handle) {
			other.handle = nullptr;
		}

		~CoroutineTask() {
			if (handle && handle.done())
				handle.destroy();
		}

		CoroutineTask& operator=(CoroutineTask&& other) noexcept {
			if (this == &other)
				return*this;
			if (handle)
				handle.destroy();
			handle = other.handle;
			other.handle = nullptr;
			return *this;
		}
	};
}
