#pragma once

#include "core/Event.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class BindableProperty;

	struct Binding {
		BindableProperty * source;
		EventHandler<BindableProperty, void*> propertyChangedHandler;
	};

	class BindableProperty {
	private:
		List<Binding*> bindings;
		RefCountedObject& owner;
		const BaseProperty& property;
		Event<BindableProperty, void*> propertyChanged = *this;

	public:
		BindableProperty(RefCountedObject& owner, const BaseProperty& property):owner(owner), property(property) {}

		BindableProperty(const BindableProperty& other):owner(owner), property(property) {}

		~BindableProperty() {
			bindings.deleteItems();
		}

		inline const AString& getName() const {
			return property.Name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline const Event<BindableProperty, void*>& getPropertyChanged() const {
			return propertyChanged;
		}

		__declspec(property(get = getPropertyChanged)) const Event<BindableProperty, void*>& PropertyChanged;

		inline void set(const void* value) const {
			property.setRaw(&owner, value);
		}

		void bindTo(BindableProperty& source);

		void unbindFrom(BindableProperty& source);
	};
}