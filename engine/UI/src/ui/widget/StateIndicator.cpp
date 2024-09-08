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

    StateIndicator::StateIndicator() {
        animation.Duration = 150;
        hoveredOrFocused.event += onStateChangedHandler;

        IndicatorState resting = { false, false };
        IndicatorState focused = { true, false };
        IndicatorState pressed = { true, true };
        stateMachine.addState(resting);
        stateMachine.addState(focused);
        stateMachine.addState(pressed);

        stateMachine.addEdge(resting, focused, [this] {
            animator.finish();
            animation.InitialValue = Color;
            animation.TargetValue = focusedColor;
            animator.start(animation, color);
        });
        stateMachine.addEdge(focused, pressed, [this] {
            animator.finish();
            animation.InitialValue = Color;
            Color = pressedColor;
        });
        stateMachine.addEdge(pressed, focused, [this] {
            animator.finish();
            animation.InitialValue = Color;
            animation.TargetValue = focusedColor;
            animator.start(animation, color);
        });
        stateMachine.addEdge(focused, resting, [this] {
            animator.finish();
            animation.InitialValue = Color;
            animation.TargetValue = idleColor;
            animator.start(animation, color);
        });
    }

    void StateIndicator::setInteractionHandler(const Ghurund::UI::InteractionHandler* interactionHandler) {
        if (this->interactionHandler) {
            this->interactionHandler->isFocused.event -= onHoveredFocusedHandler;
            this->interactionHandler->isHovered.event -= onHoveredFocusedHandler;
            this->interactionHandler->isPressed.event -= onStateChangedHandler;
        }
        this->interactionHandler = interactionHandler;
        if (this->interactionHandler) {
            this->interactionHandler->isFocused.event += onHoveredFocusedHandler;
            this->interactionHandler->isHovered.event += onHoveredFocusedHandler;
            this->interactionHandler->isPressed.event += onStateChangedHandler;
        }
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