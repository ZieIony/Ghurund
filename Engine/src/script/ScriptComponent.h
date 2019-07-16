#pragma once

#include "ecs/Component.h"
#include "Script.h"

namespace Ghurund {
	class ScriptComponent :public Component {
	private:
		Script* script = nullptr;

	public:
		ScriptComponent(Script* script) {
			Script = script;
		}

		Script* getScript() {
			return script;
		}

		void setScript(Script* script) {
			setPointer(this->script, script);
		}

		__declspec(property(get = getScript, put = setScript)) Script* Script;
	};
}