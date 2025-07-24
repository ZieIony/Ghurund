#pragma once

#include "core/exception/NullPointerException.h"

namespace Ghurund::Core {
	template <typename T>
	class OwnedNotNull {
	private:
		T* ptr;

	public:
		OwnedNotNull(T* ptr):ptr(std::move(ptr)) {
			if (!ptr)
				throw NullPointerException();
		}

		OwnedNotNull(OwnedNotNull<T>&& other) noexcept :ptr(std::move(other.ptr)) {}

		inline T* operator()() {
			return ptr;
		}

		inline T* operator&() {
			return ptr;
		}

		inline T& operator*() {
			return *ptr;
		}

		inline T* operator->() {
			return ptr;
		}

		inline bool operator==(T* other) const {
			return ptr == other;
		}
	};
}