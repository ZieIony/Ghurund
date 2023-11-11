#pragma once

#include "ui/animation/Animator.h"
#include "ui/animation/Animation.h"
#include "ui/control/ColorView.h"
#include "ui/control/ClickableControl.h"

namespace Ghurund::UI {
    enum class IndicatorState {
        NONE, FOCUSED, PRESSED
    };

    class StateIndicator:public Control {
    private:
        Color color;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        Animator animator;
        ValueAnimation<Color> animation;
        IndicatorState state = IndicatorState::NONE;

    public:
        Color idleColor = 0;
        Color focusedColor = 0;
        Color pressedColor = 0;

        StateIndicator() {
            animation.Duration = 150;
        }

        void setState(IndicatorState state);

        __declspec(property(put = setState)) IndicatorState State;

        virtual void onUpdate(uint64_t time) override {
            animator.update(time);
        }

        inline const Color& getColor() {
            return color;
        }

        inline void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        virtual void onDraw(ICanvas& canvas);

        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = StateIndicator::GET_TYPE();
    };

    class StateIndicatorOnBackgroundStyle:public Style {
    public:
        virtual void onThemeChanged(Control& control) const override;
    };

    class StateIndicatorOnAccentStyle:public Style {
    public:
        virtual void onThemeChanged(Control& control) const override;
    };
}