#pragma once

#include "MachineState.h"
#include "StateTransition.h"

#include "core/object/NotNull.h"
#include <core/collection/Map.h>
#include <core/object/IntrusivePointer.h>

namespace Ghurund::Core {
	class StateMachine {
	private:
		MachineState* currentState = nullptr;
		// TODO: use HashMap
		Map<WString, IntrusivePointer<MachineState>> states;
		Map<WString, Map<WString, IntrusivePointer<StateTransition>>> transitions;

	public:
		inline void putState(NotNull<MachineState> state) {
			auto pointer = IntrusivePointer(state.get());
			pointer->addReference();
			states.put(state->Name, pointer);
		}

		void putTransition(NotNull<StateTransition> transition);

		inline MachineState* getCurrentState() const {
			return currentState;
		}

		__declspec(property(get = getCurrentState)) MachineState* CurrentState;

		void jumpToState(const WString& name);

		void goToState(const WString& name);

		bool update();

		void reset(const WString& name);
	};
}
