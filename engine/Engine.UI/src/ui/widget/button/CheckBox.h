#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
	class CheckBox:public CheckBoxRadio<CheckBox> {
	protected:
		virtual void onLayoutChanged() override;

		virtual void onStyleStateChanged(const Ghurund::UI::Style& style, const Ghurund::UI::Theme& theme) override;

		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;
	};

	class CheckBoxStyle:public Style {
	public:
		virtual void onStateChanged(Control& control) const;

		void onStateChanged(const Theme& theme, DrawableView& drawableView, bool checked, bool enabled, bool pressed, bool hovered, bool focused) const;
	};
}