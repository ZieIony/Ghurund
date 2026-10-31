#pragma once

#include "Common.h"

#include <coroutine>
#include <exception>

namespace Ghurund::Core {
	template<>
	class CoroutineTask<void> {
	public:
		struct promise_type;

		using handle_type = std::coroutine_handle<promise_type>;

		struct promise_type {
		private:
			std::exception_ptr exception = nullptr;

		public:
			std::coroutine_handle<> continuation = std::noop_coroutine();

			CoroutineTask get_return_object() {
				return CoroutineTask(handle_type::from_promise(*this));
			}

			std::suspend_always initial_suspend() noexcept {
				return {};
			}

			auto final_suspend() noexcept {
				return FinalAwaiter<promise_type>();
			}

			void return_void() {}

			void unhandled_exception() {
				exception = std::current_exception();
				if (continuation == std::noop_coroutine())
					std::rethrow_exception(exception);
			}

			void getValue() {
				if (exception != nullptr)
					std::rethrow_exception(exception);
			}
		};

	private:
		uint32_t* referenceCount;
		handle_type handle;

		explicit CoroutineTask(handle_type handle): handle(handle), referenceCount(ghnew uint32_t(1)) {}

	public:
		CoroutineTask(
			const CoroutineTask& other
		):handle(other.handle), referenceCount(other.referenceCount) {
			(*referenceCount)++;
		}

		~CoroutineTask() {
			if (*referenceCount > 1) {
				(*referenceCount)--;
			} else {
				delete referenceCount;
				if (handle)
					handle.destroy();
			}
		}

		inline bool getIsDone() const {
			return handle.done();
		}

		__declspec(property(get = getIsDone)) bool IsDone;

		inline void resume() {
			handle.resume();
		}

		auto operator co_await() noexcept {
			return ContinuationAwaiter{ handle };
		}

		CoroutineTask& operator=(const CoroutineTask& other) {
			if (this == &other)
				return *this;
			if (*referenceCount > 1) {
				(*referenceCount)--;
			} else {
				delete referenceCount;
				if (handle)
					handle.destroy();
			}
			handle = other.handle;
			referenceCount = other.referenceCount;
			(*referenceCount)++;
			return *this;
		}
	};
}
