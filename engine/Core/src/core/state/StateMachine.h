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

		// TODO: implement this directly
		inline void jumpTo(const MachineState& state) {
			jumpTo(state.Name);
		}

		void jumpTo(const WString& name);

		// TODO: implement this directly
		inline void goTo(const MachineState& state) {
			goTo(state.Name);
		}

		void goTo(const WString& name);

		bool update();

		// TODO: implement this directly
		inline void reset(const MachineState& state) {
			reset(state.Name);
		}

		void reset(const WString& name);
	};
}
