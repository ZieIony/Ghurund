#pragma once

#include "core/Object.h"
#include "ui/theme/Theme.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
	class LayoutAttr: public Ghurund::Core::Object {
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = LayoutAttr::GET_TYPE();

		virtual SharedPointer<Control> resolve(const Theme& theme) const = 0;
	};

	class LayoutValue: public LayoutAttr {
	private:
		SharedPointer<Control> control;

	public:
		LayoutValue(Control* control):control(control) {
			if (control)
				control->addReference();
		}

		LayoutValue(const LayoutValue& other):control(other.control) {}

		LayoutValue(LayoutValue&& other) noexcept:control(std::move(other.control)) {}

		virtual SharedPointer<Control> resolve(const Theme& theme) const override {
			return control;
		}

		LayoutValue& operator=(const LayoutValue& other) {
			control = other.control;
			return *this;
		}

		LayoutValue& operator=(LayoutValue&& other) noexcept {
			if (this == &other)
				return *this;
			control = std::move(other.control);
			return *this;
		}

		virtual LayoutValue* clone() const override {
			return ghnew LayoutValue(control.get());
		}
	};

	class LayoutRef: public LayoutAttr {
	private:
		LayoutKey key;

	public:
		LayoutRef(LayoutKey key):key(key) {}

		virtual SharedPointer<Control> resolve(const Theme& theme) const override;

		virtual LayoutRef* clone() const override {
			return ghnew LayoutRef(key);
		}
	};
}
