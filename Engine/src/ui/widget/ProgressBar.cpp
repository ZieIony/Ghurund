#include "ProgressBar.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    ProgressBar::ProgressBar(Style<ProgressBar>& style) {
        style.apply(*this);
    }

    void ProgressBar::onDraw(Canvas& canvas) {
        if (indeterminate) {
            paint.Color = backgroundColor;
            canvas.fillRect(0, 0, size.width, size.height, paint);
            paint.Color = progressColor;
            canvas.fillRect(size.width * progress, 0, size.width * cos(progress * 6.28f) / 2 + 0.5f, size.height, paint);
            progress += 0.01f;
            if (progress > 1.0f)
                progress--;
            repaint();
        } else {
            paint.Color = backgroundColor;
            canvas.fillRect(size.width * progress, 0, size.width, size.height, paint);
            paint.Color = progressColor;
            canvas.fillRect(0, 0, size.width * progress, size.height, paint);
        }
    }

    ProgressBarStyle::ProgressBarStyle(Theme& theme):Style<ProgressBar>(theme) {}

    void ProgressBarStyle::onStateChanged(ProgressBar& progressBar) const {
        if (progressBar.Enabled) {
            progressBar.ProgressColor = theme.getColorAccent();
            progressBar.BackgroundColor = theme.getColorControlNormal();
        } else {
            progressBar.ProgressColor = theme.getColorControlNormal();
            progressBar.BackgroundColor = theme.getColorControlDisabled();
        }
    }
}