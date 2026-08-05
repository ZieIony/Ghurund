#pragma once

#include "core/string/String.h"
#include "core/object/RefCountedObject.h"

#include <map>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class Blackboard:public RefCountedObject {
	private:
		std::map<AString, const void*> values;

	public:
		const void* getValue(const AString& key) {
			return values[key];
		}

		inline void setValue(const AString& key, const void* value) {
			values[key] = value;
		}
	};
}
