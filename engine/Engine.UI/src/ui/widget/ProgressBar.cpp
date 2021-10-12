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
            canvas.fillRect(0, 0, Size.width, Size.height, backgroundColor->getValue(*this));
            canvas.fillRect(Size.width * progress, 0, Size.width * cos(progress * 6.28f) / 2 + 0.5f, Size.height, progressColor->getValue(*this));
            progress += 0.01f;
            if (progress > 1.0f)
                progress--;
            repaint();
        } else {
            canvas.fillRect(Size.width * progress, 0, Size.width, Size.height, backgroundColor->getValue(*this));
            canvas.fillRect(0, 0, Size.width * progress, Size.height, progressColor->getValue(*this));
        }
    }

    void ProgressBarStyle::onStateChanged(ProgressBar& control) const {
        if (control.Enabled) {
            control.ProgressColor = ColorRef(Theme::COLOR_ACCENT);
            control.BackgroundColor = ColorRef(Theme::COLOR_CONTROL);
        } else {
            control.ProgressColor = ColorRef(Theme::COLOR_CONTROL);
            control.BackgroundColor = ColorRef(Theme::COLOR_BACKGR0UND);
        }
    }
}