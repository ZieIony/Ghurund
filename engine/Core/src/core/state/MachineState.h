#pragma once

#include "core/object/RefCountedObject.h"
#include "core/string/String.h"

namespace Ghurund::Core {
	class MachineState:public RefCountedObject {
	private:
		WString name;
		bool isJumpable;

	public:
		MachineState(WString name, bool isJumpable = false):name(name), isJumpable(isJumpable) {}

		virtual ~MachineState() = 0 {}

		inline const WString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const WString& Name;

		/**
		* Jumpable states can be jumped to - state machine can go directly to this state.
		* In this case no transition will be processed. OnStateLeave and OnStateEnter will be called as usual.
		* Jump states can be connected with other states via transitions, just like regular states.
		**/
		inline bool getIsJumpable() const {
			return isJumpable;
		}

		__declspec(property(get = getIsJumpable)) bool IsJumpable;

		virtual void enter() {}

		virtual void leave() {}
	};
}
