#pragma once

#include "Script.h"

namespace Ghurund::Engine {
	class ScriptComponent {
	private:
		Script* script = nullptr;

	public:
		~ScriptComponent() {
			if (script)
				script->release();
		}

		inline Script* getScript() const {
			return script;
		}

		inline void setScript(Script* script) {
			setPointer(this->script, script);
		}

		__declspec(property(get = getScript, put = setScript)) Script* Script;
	};
}
