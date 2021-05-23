#pragma once

namespace Ghurund {
	template<typename T>
	class TypeWrapper {
	private:
		T value;

	public:
		TypeWrapper(T&& value): value(std::move(value)) {}

		explicit TypeWrapper(const T& value): value(value) {}

		inline T& getValue() {
			return value;
		}

		inline const T& getValue() const {
			return value;
		}

		inline void setValue(const T& value) {
			this->value = value;
		}

		__declspec(property(get = getValue, put = setValue)) T& Value;

		inline operator const T& () const {
			return value;
		}

		inline operator T& () {
			return value;
		}

		inline TypeWrapper<T>& operator=(const T& value) {
			this->value = value;
			return *this;
		}

		inline bool operator==(const TypeWrapper<T>& other) const {
			return other.value == value;
		}
	};
}