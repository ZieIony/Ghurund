#pragma once

namespace Ghurund::Core {
	template <typename T>
	class PointerWrapper {
	private:
		T* value;

		PointerWrapper(const PointerWrapper& other) = delete;

	public:
		PointerWrapper(T* pointer): value(pointer) {}

		PointerWrapper(PointerWrapper&& other) {
			value = other->value;
			other->value = nullptr;
		}

		~PointerWrapper() {
			delete value;
		}

		inline T* operator->() {
			return value;
		}
	};
}