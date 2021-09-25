#include "ghuipch.h"
#include "ProgressBar.h"

#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ProgressBar::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ProgressBar>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ProgressBar>(NAMESPACE_NAME, GH_STRINGIFY(ProgressBar))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ProgressBar::onDraw(Canvas& canvas) {
        if (indeterminate) {
            canvas.fillRect(0, 0, Size.width, Size.height, backgroundColor);
            canvas.fillRect(Size.width * progress, 0, Size.width * cos(progress * 6.28f) / 2 + 0.5f, Size.height, progressColor);
            progress += 0.01f;
            if (progress > 1.0f)
                progress--;
            repaint();
        } else {
            canvas.fillRect(Size.width * progress, 0, Size.width, Size.height, backgroundColor);
            canvas.fillRect(0, 0, Size.width * progress, Size.height, progressColor);
        }
    }

    void ProgressBarStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((ProgressBar&)control).ProgressColor = theme->Colors[Theme::COLOR_ACCENT];
        ((ProgressBar&)control).BackgroundColor = theme->Colors[Theme::COLOR_CONTROL];
    }

    void ProgressBarStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (control.Enabled) {
            ((ProgressBar&)control).ProgressColor = theme->Colors[Theme::COLOR_ACCENT];
            ((ProgressBar&)control).BackgroundColor = theme->Colors[Theme::COLOR_CONTROL];
        } else {
            ((ProgressBar&)control).ProgressColor = theme->Colors[Theme::COLOR_CONTROL];
            ((ProgressBar&)control).BackgroundColor = theme->Colors[Theme::COLOR_BACKGR0UND];
        }
    }
}