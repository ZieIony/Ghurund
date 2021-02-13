#include "ProgressBar.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void ProgressBar::onDraw(Canvas& canvas) {
        if (indeterminate) {
            paint.Color = backgroundColor;
            canvas.fillRect(0, 0, Size.width, Size.height, paint);
            paint.Color = progressColor;
            canvas.fillRect(Size.width * progress, 0, Size.width * cos(progress * 6.28f) / 2 + 0.5f, Size.height, paint);
            progress += 0.01f;
            if (progress > 1.0f)
                progress--;
            repaint();
        } else {
            paint.Color = backgroundColor;
            canvas.fillRect(Size.width * progress, 0, Size.width, Size.height, paint);
            paint.Color = progressColor;
            canvas.fillRect(0, 0, Size.width * progress, Size.height, paint);
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