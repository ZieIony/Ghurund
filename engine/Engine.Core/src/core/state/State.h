#pragma once

#include "core/Event.h"

namespace Ghurund::Core {
	template<typename Type>
	class State {
	private:
		Type value;

	public:
		mutable Event<State, Type> event = *this;

		State(Type initial):value(initial) {}

		inline Type getValue() const {
			return value;
		}

		inline void setValue(const Type& value) {
			if (this->value == value)
				return;
			this->value = value;
			event(value);
		}

		__declspec(property(get = getValue, put = setValue)) Type Value;
	};
}