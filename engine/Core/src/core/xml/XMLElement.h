#pragma once

#include "core/DataParsing.h"
#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/object/SharedPointer.h"
#include "core/string/String.h"

namespace Ghurund::Core {
	struct XMLElement {
		WString name, value;
		Map<WString, WString> attributes;
		List<SharedPointer<XMLElement>> children;

		template<typename T>
		inline T getAttributeValue(const WString& name) const {
			auto attr = requireAttribute(name);
			AString aStrAttr = convertText<wchar_t, char>(attr);
			return parse<T>(*aStrAttr);
		}

		template<typename T>
		inline T getAttributeValue(const WString& name, T defaultValue) const {
			auto attr = findAttribute(name);
			if (!attr)
				return defaultValue;
			AString aStrAttr = convertText<wchar_t, char>(*attr);
			return parse<T>(aStrAttr);
		}

		inline WString* findAttribute(const WString& name) const {
			auto it = attributes.find(name);
			if (it != attributes.end())
				return &it->value;
			return nullptr;
		}

		inline const WString& requireAttribute(const WString& name) const {
			auto attr = findAttribute(name);
			if (!attr) {
				auto message = std::format(_T("Required attribute '{}' on node '{}' is missing.\n"), this->name, name);
				Logger::logAndThrow<InvalidDataException>(message.c_str());
			}
			return *attr;
		}

		inline XMLElement* findElement(const WString& name) const {
			auto index = children.find([&](auto& child) {return child->name == name; });
			if (index != children.Size)
				return children[index].get();
			return nullptr;
		}

		inline const XMLElement& requireElement(const WString& name) const {
			auto element = findElement(name);
			if (!element) {
				auto message = std::format(_T("Required node '{}' on node '{}' is missing.\n"), this->name, name);
				Logger::logAndThrow<InvalidDataException>(message.c_str());
			}
			return *element;
		}
	};
}
