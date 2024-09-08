#include "ghuipch.h"
#include "RadioButton.h"

#include "ui/control/DrawableView.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& RadioButton::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<RadioButton>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<RadioButton>(NAMESPACE_NAME, GH_STRINGIFY(RadioButton))
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void RadioButton::onStateChanged() {
		if (drawable) {
			if (checked) {
				drawable->Drawable = Theme::DRAWABLE_RADIOBUTTON_CHECKED;
			} else {
				drawable->Drawable = Theme::DRAWABLE_RADIOBUTTON_UNCHECKED;
			}
			if (!Enabled) {
				drawable->Tint = Theme::COLOR_DISABLED_ONBACKGROUND;
			} else if (interactionHandler.isPressed) {
				if (checked) {
					drawable->Tint = Theme::COLOR_ACCENT;
				} else {
					drawable->Tint = Theme::COLOR_PRIMARY_ONBACKGROUND;
				}
			} else if (interactionHandler.isHovered || Focused) {
				if (checked) {
					drawable->Tint = Theme::COLOR_ACCENT;
				} else {
					drawable->Tint = Theme::COLOR_SECONDARY_ONBACKGROUND;
				}
			} else {
				if (checked) {
					drawable->Tint = Theme::COLOR_ACCENT;
				} else {
					drawable->Tint = Theme::COLOR_SECONDARY_ONBACKGROUND;
				}
			}
		}
	}
}