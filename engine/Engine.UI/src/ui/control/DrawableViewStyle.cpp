#include "ghuipch.h"
#include "DrawableViewStyle.h"
#include "DrawableView.h"

namespace Ghurund::UI {

    void DrawableViewStyle::onStateChanged(Control& control) const {
        DrawableView& drawableView = ((DrawableView&)control);
        /*if (control.Enabled) {
            drawableView.Alpha = 1.0f;
        } else {
            drawableView.Alpha = 0.38f;
        }*/
    }

    void DrawableViewOnBackgroundStyle::onStateChanged(Control& control) const {
        DrawableView& drawableView = ((DrawableView&)control);
        if (control.Enabled) {
            drawableView.Tint = Theme::COLOR_PRIMARY_ONBACKGROUND;
        } else {
            drawableView.Tint = Theme::COLOR_DISABLED_ONBACKGROUND;
        }
    }

    void DrawableViewOnAccentStyle::onStateChanged(Control& control) const {
        DrawableView& drawableView = ((DrawableView&)control);
        if (control.Enabled) {
            drawableView.Tint = Theme::COLOR_PRIMARY_ONACCENT;
        } else {
            drawableView.Tint = Theme::COLOR_DISABLED_ONACCENT;
        }
    }

    void DrawableViewAccentStyle::onStateChanged(Control& control) const {
        DrawableView& drawableView = ((DrawableView&)control);
        if (control.Enabled) {
            drawableView.Tint = Theme::COLOR_ACCENT;
        } else {
            drawableView.Tint = Theme::COLOR_DISABLED_ONBACKGROUND;
        }
    }
}