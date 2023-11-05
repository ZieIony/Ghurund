#include "ghuipch.h"
#include "StateIndicator.h"

#include "ui/Canvas.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    void StateIndicator::onThemeChanged() {
        const Ghurund::UI::Theme* theme = Theme;
        if (!theme)
            return;
        focusedColor = theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND];
        pressedColor = ((focusedColor >> 24) * 2) << 24 | focusedColor & 0xffffff;
        idleColor = focusedColor & 0xffffff;
    }

    void StateIndicator::onDraw(ICanvas& canvas) {
        if (color.A > 0.0f) {
            canvas.Color = color;
            canvas.fillRect(0, 0, Size.Width, Size.Height);
        }
    }

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

    void StateIndicatorOnAccent::onThemeChanged() {
        const Ghurund::UI::Theme* theme = Theme;
        if (!theme)
            return;
        focusedColor = theme->Colors[Theme::COLOR_HIGHLIGHT_ONACCENT];
        pressedColor = ((focusedColor >> 24) * 2) << 24 | focusedColor & 0xffffff;
        idleColor = focusedColor & 0xffffff;
    }

    const Ghurund::Core::Type& StateIndicatorOnAccent::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<StateIndicatorOnAccent>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<StateIndicatorOnAccent>(NAMESPACE_NAME, GH_STRINGIFY(StateIndicatorOnAccent))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}