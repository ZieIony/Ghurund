#pragma once

#include "core/exception/NullPointerException.h"

namespace Ghurund::Core {
	template <typename T>
	class NotNull {
	private:
		T* ptr;

	public:
		NotNull(T& ref):ptr(&ref) {}

		NotNull(T* ptr):ptr(ptr) {
			if (!ptr)
				throw NullPointerException();
		}

		NotNull(const NotNull<T>& other):ptr(other.ptr) {}

		NotNull(NotNull<T>&& other):ptr(std::move(other.ptr)) {}

		inline T* operator()() const {
			return ptr;
		}

		inline T* get() const {
			return ptr;
		}

		inline T* operator&() {
			return ptr;
		}

		inline T& ref() {
			return *ptr;
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