#include "ghuipch.h"
#include "ProgressBar.h"

#include "ui/theme/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ProgressBar::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<ProgressBar>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<ProgressBar>(NAMESPACE_NAME, GH_STRINGIFY(ProgressBar))
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ProgressBar::onThemeChanged() {
		const UI::Theme* theme = Theme;
		if (theme) {
			backgroundColor.resolve(*theme);
			progressColor.resolve(*theme);
		}
	}

	void ProgressBar::onStateChanged() {
		if (Enabled) {
			ProgressColor = ColorRef(Theme::COLOR_ACCENT);
			BackgroundColor = ColorRef(Theme::COLOR_CONTROL);
		} else {
			ProgressColor = ColorRef(Theme::COLOR_CONTROL);
			BackgroundColor = ColorRef(Theme::COLOR_BACKGR0UND);
		}
	}

	void ProgressBar::onDraw(ICanvas& canvas) {
		if (indeterminate) {
			const Color* bgColor = backgroundColor.get();
			if (bgColor) {
				canvas.Color = *bgColor;
				canvas.fillRect(0, 0, Size.Width, Size.Height);
			}
			const Color* prColor = progressColor.get();
			if (prColor) {
				canvas.Color = *prColor;
				canvas.fillRect(Size.Width * progress, 0, Size.Width * cos(progress * 6.28f) / 2 + 0.5f, Size.Height);
			}
			progress += 0.01f;
			if (progress > 1.0f)
				progress--;
			repaint();
		} else {
			const Color* bgColor = backgroundColor.get();
			if (bgColor) {
				canvas.Color = *bgColor;
				canvas.fillRect(Size.Width * progress, 0, Size.Width, Size.Height);
			}
			const Color* prColor = progressColor.get();
			if (prColor) {
				canvas.Color = *prColor;
				canvas.fillRect(0, 0, Size.Width * progress, Size.Height);
			}
		}
	}
}