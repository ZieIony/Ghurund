#pragma once

#include "core/object/RefCountedObject.h"
#include "core/string/String.h"

namespace Ghurund::Core {
	class StateTransition:public RefCountedObject {
	private:
		WString from, to;

	protected:
		virtual void onExecute() {}

	public:
		StateTransition(const WString& from, const WString& to):from(from), to(to) {}

		virtual ~StateTransition() {};

		inline const WString& getFrom() const {
			return from;
		}

		__declspec(property(get = getFrom)) const WString& From;

		inline const WString& getTo() const {
			return to;
		}

		__declspec(property(get = getTo)) const WString& To;

		virtual bool shouldTransition() {
			return true;
		}

		inline void execute() {
			onExecute();
		}
	};
}
