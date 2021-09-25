#include "ghuipch.h"
#include "StateIndicator.h"

#include "ui/Canvas.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& StateIndicator::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<StateIndicator>();
        static const Ghurund::Core::Type& TYPE = TypeBuilder<StateIndicator>(NAMESPACE_NAME, GH_STRINGIFY(StateIndicator))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void StateIndicator::setState(IndicatorState state) {
        if (this->state == state)
            return;
        animation.ProgressChanged.clear();
        prevColor = Color;
        if (state == IndicatorState::FOCUSED) {
            if (this->state > state) {
                animation.ProgressChanged.add([this](Animation& animation) {
                    Color = lerpColors(prevColor, focusedColor, animation.Progress);
                    return true;
                });
            } else {
                Color = focusedColor;
            }
        } else if (state == IndicatorState::PRESSED) {
            Color = pressedColor;
        } else {
            animation.ProgressChanged.add([this](Animation& animation) {
                Color = lerpColors(prevColor, idleColor, animation.Progress);
                return true;
            });
        }
        this->state = state;
        animation.start();
    }

    void StateIndicator::onDraw(Canvas& canvas) {
        canvas.fillRect(0, 0, Size.width, Size.height, color);
    }

    void StateIndicatorOnBackgroundStyle::onThemeChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        StateIndicator& indicator = (StateIndicator&)control;
        indicator.focusedColor = theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND];
        indicator.pressedColor = ((indicator.focusedColor >> 24) * 2) << 24 | indicator.focusedColor & 0xffffff;
        indicator.idleColor = indicator.focusedColor & 0xffffff;
    }

    void StateIndicatorOnAccentStyle::onThemeChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        StateIndicator& indicator = (StateIndicator&)control;
        indicator.focusedColor = theme->Colors[Theme::COLOR_HIGHLIGHT_ONACCENT];
        indicator.pressedColor = ((indicator.focusedColor >> 24) * 2) << 24 | indicator.focusedColor & 0xffffff;
        indicator.idleColor = indicator.focusedColor & 0xffffff;
    }
}