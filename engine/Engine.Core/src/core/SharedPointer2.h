#pragma once

#include "Common.h"
#include "core/concepts/Concepts.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
	template<typename T>
	class SharedPointer2 {
	private:
		uint32_t* referenceCount;
		T* pointer;

	public:
		constexpr SharedPointer2():pointer(nullptr), referenceCount(ghnew uint32_t(1)) {}

		SharedPointer2(const SharedPointer2<T>& other) {
			pointer = other.pointer;
			referenceCount = other.referenceCount;
			(*referenceCount)++;
		}

		SharedPointer2(SharedPointer2<T>&& other) noexcept {
			pointer = other.pointer;
			other.pointer = nullptr;
			referenceCount = other.referenceCount;
			other.referenceCount = nullptr;
		}

		explicit SharedPointer2(T* p):referenceCount(ghnew uint32_t(1)) {
			pointer = p;
		}

		~SharedPointer2() {
			if (*referenceCount > 1) {
				(*referenceCount)--;
			} else {
				delete referenceCount;
				delete pointer;
			}
		}

		inline T* get() const {
			return pointer;
		}

		inline void set(T* p) {
			if (*referenceCount > 1) {
				(*referenceCount)--;
			} else {
				delete pointer;
			}
			pointer = p;
			*referenceCount = 1;
		}

		uint32_t getReferenceCount() const {
			return *referenceCount;
		}

		__declspec(property(get = getReferenceCount)) uint32_t ReferenceCount;

		inline T* operator ->() {
			return pointer;
		}

		inline const T* operator ->() const {
			return pointer;
		}

		inline SharedPointer2<T>& operator=(const SharedPointer2<T>& other) {
			if (*this == other)
				return *this;
			if (*referenceCount > 1) {
				(*referenceCount)--;
			} else {
				delete referenceCount;
				delete pointer;
			}
			pointer = other.pointer;
			referenceCount = other.referenceCount;
			if (pointer) {
				(*referenceCount)++;
			}
			return *this;
		}

		inline SharedPointer2<T>& operator=(SharedPointer2<T>&& other) noexcept {
			if (*referenceCount > 1) {
				(*referenceCount)--;
			} else {
				delete referenceCount;
				delete pointer;
			}
			pointer = other.pointer;
			other.pointer = nullptr;
			referenceCount = other.referenceCount;
			other.referenceCount = nullptr;
			return *this;
		}

		inline bool operator==(const SharedPointer2<T>& other) const {
			return referenceCount == other.referenceCount;
		}

		inline bool operator==(const nullptr_t& other) const {
			return pointer == nullptr;
		}
	};
}