#pragma once

#include "core/Event.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class BindableProperty;

	struct Binding {
		BindableProperty * source;
		EventHandler<BindableProperty, bool, void*> propertyChangedHandler;
	};

	class BindableProperty {
	private:
		List<Binding*> bindings;
		RefCountedObject& owner;
		const BaseProperty& property;

	public:
		Event<BindableProperty, void, void*> propertyChanged = *this;

		BindableProperty(RefCountedObject& owner, const BaseProperty& property):owner(owner), property(property) {}

		BindableProperty(const BindableProperty& other):owner(owner), property(property) {}

		~BindableProperty() {
			bindings.deleteItems();
		}

		inline const AString& getName() const {
			return property.Name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline void set(const void* value) const {
			property.setRaw(&owner, value);
		}

		void bindTo(BindableProperty& source);

		void unbindFrom(BindableProperty& source);
	};
}