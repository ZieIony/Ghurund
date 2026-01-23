#pragma once

#include "RefCountedObject.h"
#include "Common.h"
#include "core/concepts/Concepts.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
	template<Derived<RefCountedObject> T>
	class IntrusivePointer {
	private:
		T* pointer = nullptr;

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			Ghurund::Core::getType<T>();
			static const Type TYPE = TypeBuilder<IntrusivePointer<T>>()
				.withTemplateParam<T>();
			return TYPE;
		}

		inline static const Type& TYPE = GET_TYPE();

		constexpr IntrusivePointer():pointer(nullptr) {}

		IntrusivePointer(const IntrusivePointer<T>& other) {
			pointer = other.get();
			if (pointer)
				pointer->addReference();
		}

		template<Derived<T> R>
		IntrusivePointer(const IntrusivePointer<R>& other) {
			pointer = other.get();
			if (pointer)
				pointer->addReference();
		}

		IntrusivePointer(IntrusivePointer<T>&& other) noexcept {
			pointer = other.pointer;
			other.pointer = nullptr;
		}

		template<Derived<T> R>
		IntrusivePointer(IntrusivePointer<R>&& other) noexcept {
			// TODO: this doesn't work because pointer is private in other template uses
			pointer = other.pointer;
			other.pointer = nullptr;
		}

		explicit IntrusivePointer(T* p) {
			pointer = p;
		}

		~IntrusivePointer() {
			if (pointer)
				pointer->release();
		}

		inline T* get() const {
			return pointer;
		}

		inline T& ref() const {
			return *pointer;
		}

		inline void set(T* p) {
			if (pointer)
				pointer->release();
			pointer = p;
		}

		uint32_t getReferenceCount() const {
			return pointer ? pointer->ReferenceCount : 0;
		}

		__declspec(property(get = getReferenceCount)) uint32_t ReferenceCount;

		inline T* operator ->() {
			return pointer;
		}

		inline const T* operator ->() const {
			return pointer;
		}

		inline IntrusivePointer<T>& operator=(const IntrusivePointer<T>& other) {
			setPointer(pointer, other.get());
			return *this;
		}

		template<Derived<T> R>
		inline IntrusivePointer<T>& operator=(const IntrusivePointer<R>& other) {
			setPointer(pointer, (T*)other.get());
			return *this;
		}

		inline IntrusivePointer<T>& operator=(IntrusivePointer<T>&& other) noexcept {
			if (pointer)
				pointer->release();
			pointer = other.pointer;
			other.pointer = nullptr;
			return *this;
		}

		template<Derived<T> R>
		inline auto operator<=>(const IntrusivePointer<R>& other) const {
			return pointer <=> other.get();
		}

		template<Derived<T> R>
		inline bool operator==(const IntrusivePointer<R>& other) const {
			return pointer == other.get();
		}

		inline bool operator==(const nullptr_t& other) const {
			return pointer == nullptr;
		}
	};

	template<typename T, typename... Args>
	IntrusivePointer<T> makeIntrusive(Args&&... args) {
		return IntrusivePointer(ghnew T(std::forward<Args>(args)...));
	}
}