#pragma once

#include "BindableProperty.h"

#include "core/collection/Map.h"
#include "core/string/String.h"
#include "core/object/NotNull.h"

namespace Ghurund::UI {
	class BindablePropertyCollection {
	private:
		Map<AString, BindableProperty*> properties;

	public:
		inline BindableProperty& get(const AString& name) {
			return *properties.get(name);
		}

		inline void add(NotNull<BindableProperty> property) {
			properties.put(property->Name, property.get());
		}
	};
}