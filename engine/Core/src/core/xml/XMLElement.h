#pragma once

#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/object/SharedPointer.h"
#include "core/string/String.h"

namespace Ghurund::Core {
	struct XMLElement {
		WString name, value;
		Map<WString, WString> attributes;
		List<SharedPointer<XMLElement>> children;

		inline WString* findAttribute(const WString& name) const {
			auto it = attributes.find(name);
			if (it != attributes.end())
				return &it->value;
			return nullptr;
		}

		inline XMLElement* findElement(const WString& name) const {
			auto index = children.find([&](auto& child) {return child->name == name; });
			if (index != children.Size)
				return children[index].get();
			return nullptr;
		}
	};
}
