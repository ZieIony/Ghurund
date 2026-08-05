#include "ghuipch.h"
#include "BindableProperty.h"

namespace Ghurund::UI {
	void BindableProperty::bindTo(BindableProperty& source) {
		EventHandler<BindableProperty, bool, void*> propertyChangedHandler = [&](BindableProperty&, void* value) {
			set(value);
			return true;
		};
		source.propertyChanged += propertyChangedHandler;
		auto binding = ghnew Binding(&source, propertyChangedHandler);
		bindings.add(binding);
	}

	inline void BindableProperty::unbindFrom(BindableProperty& source) {
		auto index = bindings.find([&](const auto& binding) {return binding->source == &source; });
		if (index != bindings.Size) {
			Binding* binding = bindings.get(index);
			bindings.removeAt(index);
			binding->source->propertyChanged -= binding->propertyChangedHandler;
		}
	}
}