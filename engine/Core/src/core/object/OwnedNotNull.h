#pragma once

#include "Object.h"
#include "core/exception/NullPointerException.h"
#include "DefaultDeleter.h"

namespace Ghurund::Core {
	template <typename T, typename D = DefaultDeleter<T>>
	class OwnedNotNull {
	private:
		T* ptr;

	public:
		explicit OwnedNotNull(T* ptr):ptr(ptr) {
			if (!ptr)
				throw NullPointerException();
		}

		OwnedNotNull(const OwnedNotNull& other) = delete;

		OwnedNotNull(OwnedNotNull&& other) noexcept :ptr(std::move(other.ptr)) {
			other.ptr = nullptr;
		}

		~OwnedNotNull() {
			D()(ptr);
		}

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

		inline T* reset() {
			T* copy = ptr;
			ptr = nullptr;
			return copy;
		}

		inline bool operator==(T* other) const {
			return ptr == other;
		}
	};
}