#include "StateIndicator.h"

#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::UI::Style& StateIndicator::DEFAULT_STYLE = StateIndicatorStyle();

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
                Color = lerpColors(prevColor, 0, animation.Progress);
                return true;
            });
        }
        this->state = state;
        animation.start();
    }

    void StateIndicatorStyle::onThemeChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        StateIndicator& indicator = (StateIndicator&)control;
        indicator.focusedColor = theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND];
        indicator.pressedColor = indicator.focusedColor * 2;
    }
}