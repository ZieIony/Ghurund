#pragma once

#include "Script.h"

#include "core/collection/Map.h"
#include "core/concepts/Derived.h"
#include "core/reflection/Type.h"
#include "core/string/String.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ScriptManager:Noncopyable {
	private:
		Map<WString, const Type*> scripts;

	public:
		template<Derived<Script> T>
		inline void registerScript() {
			scripts.put(convertText<char, wchar_t>(T::TYPE.Name), &T::TYPE);
		}

		inline Script* makeScript(const WString& name) {
			return (Script*)scripts.get(name)->Constructors[0].get().invokeRaw();
		}
	};
}
