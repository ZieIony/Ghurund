#include "StateIndicator.h"

#include "core/reflection/TypeBuilder.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Type& StateIndicator::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<StateIndicator>();
        static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(StateIndicator))
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
        if (!paint.Color)
            return;
        canvas.fillRect(0, 0, Size.width, Size.height, paint);
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