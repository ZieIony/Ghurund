#include "ghuipch.h"
#include "CheckBox.h"

#include "ui/control/DrawableView.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	void CheckBox::onStateChanged() {
		if (drawable) {
			if (checked) {
				drawable->Drawable = Theme::DRAWABLE_CHECKBOX_CHECKED;
			} else {
				drawable->Drawable = Theme::DRAWABLE_CHECKBOX_UNCHECKED;
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

	const Ghurund::Core::Type& CheckBox::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<CheckBox>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBox>(NAMESPACE_NAME, GH_STRINGIFY(CheckBox))
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}