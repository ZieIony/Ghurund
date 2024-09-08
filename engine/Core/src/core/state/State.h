#pragma once

#include "core/Event.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Core {
	template<typename T>
	class State {
	private:
		T value;

	public:
		mutable Event<State, T> event = *this;

		State(T initial):value(initial) {}

		inline operator const T& () const {
			return value;
		}

		inline const T& operator=(const T& value) {
			if (this->value != value) {
				this->value = value;
				event(this->value);
			}
			return this->value;
		}
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<State<bool>>();
}