#include "ghuipch.h"
#include "CheckBox.h"

#include "ui/control/DrawableView.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	void CheckBox::onLayoutChanged() {
		if (clickable) {
			clickable->clicked.clear();
			clickable->stateChanged.clear();
		}
		__super::onLayoutChanged();
		if (clickable) {
			clickable->clicked += [this](Control&, const MouseClickedEventArgs&) {
				Checked = !checked;
				return true;
				};
			clickable->stateChanged += stateHandler;
		}
	}

	void CheckBox::onStyleStateChanged(const Ghurund::UI::Style& style, const Ghurund::UI::Theme& theme) {
		__super::onStyleStateChanged(style, theme);
		if (drawable && clickable) {
			CheckBoxStyle& checkBoxStyle = (CheckBoxStyle&)style;
			checkBoxStyle.onStateChanged(theme, *drawable, checked, Enabled, clickable->Pressed, clickable->Hovered, Focused);
		}
	}

	const Ghurund::Core::Type& CheckBox::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<CheckBox>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBox>(NAMESPACE_NAME, GH_STRINGIFY(CheckBox))
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void CheckBoxStyle::onStateChanged(Control& control) const {
		const Theme* theme = control.Theme;
		if (!theme)
			return;
		CheckBox& checkBox = (CheckBox&)control;
		/*if (checkBox->clickable->Selected) {
			SharedPointer<ImageDrawable> drawable = (ImageDrawable*)theme->Drawables[Theme::DRAWABLE_CHECKBOX_CHECKED]->clone();
			checkBox->drawable->Image = drawable;
		} else {
			SharedPointer<ImageDrawable> drawable = (ImageDrawable*)theme->Drawables[Theme::DRAWABLE_CHECKBOX_UNCHECKED]->clone();
			checkBox->drawable->Image = drawable;
		}
		if (!control.Enabled) {
			layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND));
		} else if (layout->Selectable->Pressed) {
			if (layout->Selectable->Selected) {
				//drawableView->Image->Tint = theme->getColorAccentDark();
				layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_ACCENT));
			} else {
				layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND));
			}
		} else if (layout->Selectable->Hovered || layout->Selectable->Focused) {
			if (layout->Selectable->Selected) {
				layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_ACCENT));
			} else {
				layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND));
			}
		} else {
			if (layout->Selectable->Selected) {
				layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_ACCENT));
			} else {
				layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND));
			}
		}*/
	}

	void CheckBoxStyle::onStateChanged(const Theme& theme, DrawableView& drawableView, bool checked, bool enabled, bool pressed, bool hovered, bool focused) const {
		if (checked) {
			drawableView.Drawable = Theme::DRAWABLE_CHECKBOX_CHECKED;
		} else {
			drawableView.Drawable = Theme::DRAWABLE_CHECKBOX_UNCHECKED;
		}
		if (!enabled) {
			drawableView.Tint = Theme::COLOR_DISABLED_ONBACKGROUND;
		} else if (pressed) {
			if (checked) {
				drawableView.Tint = Theme::COLOR_ACCENT;
			} else {
				drawableView.Tint = Theme::COLOR_PRIMARY_ONBACKGROUND;
			}
		} else if (hovered || focused) {
			if (checked) {
				drawableView.Tint = Theme::COLOR_ACCENT;
			} else {
				drawableView.Tint = Theme::COLOR_SECONDARY_ONBACKGROUND;
			}
		} else {
			if (checked) {
				drawableView.Tint = Theme::COLOR_ACCENT;
			} else {
				drawableView.Tint = Theme::COLOR_SECONDARY_ONBACKGROUND;
			}
		}
	}
}