#pragma once

#include "Common.h"
#include "RefCountedObject.h"
#include "core/exception/Exceptions.h"

namespace Ghurund::Core {
	template<typename T>
	class SharedPointer {
	private:
		uint32_t* referenceCount;
		T* pointer;

	public:
		constexpr SharedPointer():pointer(nullptr), referenceCount(ghnew uint32_t(1)) {}

		SharedPointer(const SharedPointer<T>& other) {
			pointer = other.pointer;
			referenceCount = other.referenceCount;
			(*referenceCount)++;
		}

		explicit SharedPointer(T* p):referenceCount(ghnew uint32_t(1)) {
			pointer = p;
		}

		~SharedPointer() {
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

		inline SharedPointer<T>& operator=(const SharedPointer<T>& other) {
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

		inline auto operator<=>(const SharedPointer<T>& other) const {
			if (pointer == other.pointer)
				return referenceCount <=> other.referenceCount;
			return pointer <=> other.pointer;
		}

		inline bool operator==(const SharedPointer<T>& other) const {
			return pointer == other.pointer && referenceCount == other.referenceCount;
		}

		inline bool operator==(const nullptr_t& other) const {
			return pointer == nullptr;
		}
	};

	template<typename T, typename... Args>
	SharedPointer<T> makeShared(Args&&... args) {
		return SharedPointer(ghnew T(std::forward<Args>(args)...));
	}

	template<std::derived_from<RefCountedObject> T, typename... Args>
	SharedPointer<T> makeShared(Args&&... args) = delete;
}