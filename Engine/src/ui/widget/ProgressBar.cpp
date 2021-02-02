#include "ProgressBar.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    ProgressBar::ProgressBar(Style<ProgressBar>& style):ProgressBar() {
        style.apply(*this);
    }

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

    void ProgressBarStyle::onThemeChanged(ProgressBar& progressBar) const {
        Ghurund::UI::Theme* theme = progressBar.Theme;
        if (!theme)
            return;
        progressBar.ProgressColor = theme->Colors[Theme::COLOR_ACCENT];
        progressBar.BackgroundColor = theme->getColorControlNormal();
    }

    void ProgressBarStyle::onStateChanged(ProgressBar& progressBar) const {
        Ghurund::UI::Theme* theme = progressBar.Theme;
        if (!theme)
            return;
        if (progressBar.Enabled) {
            progressBar.ProgressColor = theme->Colors[Theme::COLOR_ACCENT];
            progressBar.BackgroundColor = theme->getColorControlNormal();
        } else {
            progressBar.ProgressColor = theme->getColorControlNormal();
            progressBar.BackgroundColor = theme->getColorControlDisabled();
        }
    }
}