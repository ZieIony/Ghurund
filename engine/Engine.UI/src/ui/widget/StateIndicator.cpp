#include "ghuipch.h"
#include "StateIndicator.h"

#include "ui/Canvas.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& StateIndicator::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<StateIndicator>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<StateIndicator>(NAMESPACE_NAME, GH_STRINGIFY(StateIndicator))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void StateIndicator::setState(IndicatorState state) {
        if (this->state == state)
            return;
        animator.finish();
        animation.InitialValue = Color;
        if (state == IndicatorState::FOCUSED) {
            if (this->state > state) {
                animation.TargetValue = focusedColor;
                animator.start(animation, color);
            } else {
                Color = focusedColor;
            }
        } else if (state == IndicatorState::PRESSED) {
            Color = pressedColor;
        } else {
            animation.TargetValue = idleColor;
            animator.start(animation, color);
        }
        this->state = state;
    }

    void StateIndicator::onDraw(ICanvas& canvas) {
        if (color.A > 0.0f) {
            canvas.Color = color;
            canvas.fillRect(0, 0, Size.Width, Size.Height);
        }
    }

    void StateIndicatorOnBackgroundStyle::onThemeChanged(Control& control) const {
        const Theme* theme = control.Theme;
        if (!theme)
            return;
        StateIndicator& indicator = (StateIndicator&)control;
        indicator.focusedColor = theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND];
        indicator.pressedColor = ((indicator.focusedColor >> 24) * 2) << 24 | indicator.focusedColor & 0xffffff;
        indicator.idleColor = indicator.focusedColor & 0xffffff;
    }

    void StateIndicatorOnAccentStyle::onThemeChanged(Control& control) const {
        const Theme* theme = control.Theme;
        if (!theme)
            return;
        StateIndicator& indicator = (StateIndicator&)control;
        indicator.focusedColor = theme->Colors[Theme::COLOR_HIGHLIGHT_ONACCENT];
        indicator.pressedColor = ((indicator.focusedColor >> 24) * 2) << 24 | indicator.focusedColor & 0xffffff;
        indicator.idleColor = indicator.focusedColor & 0xffffff;
    }
}