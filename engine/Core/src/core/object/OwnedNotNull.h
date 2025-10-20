#pragma once

#include "DefaultDeleter.h"
#include "Object.h"
#include "core/concepts/Concepts.h"
#include "core/exception/NullPointerException.h"

namespace Ghurund::Core {
	template <typename T, typename D = DefaultDeleter<T>>
	class OwnedNotNull {
	private:
		T* ptr;

	public:
		template<Derived<T> R>
		explicit OwnedNotNull(R* ptr):ptr(ptr) {
			if (!ptr)
				throw NullPointerException();
		}

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

		inline bool operator==(const OwnedNotNull& other) const {
			return ptr == other.ptr;
		}

		inline OwnedNotNull& operator=(OwnedNotNull&& other) noexcept {
			if (*this == other)
				return *this;
			delete ptr;
			ptr = std::move(other.ptr);
			other.ptr = nullptr;
			return *this;
		}
	};
}