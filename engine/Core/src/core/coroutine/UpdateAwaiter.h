#pragma once

#include "core/collection/List.h"

#include <coroutine>

namespace Ghurund::Core {
	class UpdateAwaiter {
	private:
		List<UpdateAwaiter>& updateAwaiters;
		std::coroutine_handle<> handle;

	public:
		UpdateAwaiter(List<UpdateAwaiter>& updateAwaiters):updateAwaiters(updateAwaiters) {}

		UpdateAwaiter(const UpdateAwaiter& other):updateAwaiters(other.updateAwaiters), handle(other.handle) {}

		bool await_ready() const {
			return false;
		}

		bool await_suspend(std::coroutine_handle<> handle) {
			this->handle = handle;
			updateAwaiters.add(*this);
			return true;
		}

		void await_resume() const {}

		UpdateAwaiter& operator=(const UpdateAwaiter& other) {
			if (this == &other)
				return *this;
			handle = other.handle;
			return *this;
		}

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
