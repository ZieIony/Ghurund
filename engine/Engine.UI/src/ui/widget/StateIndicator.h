#pragma once

#include "ui/Animation.h"
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
        static const Ghurund::Core::Type& GET_TYPE();

        Animation animation;
        IndicatorState state = IndicatorState::NONE;
        Color prevColor = 0;

    public:
        Color idleColor = 0;
        Color focusedColor = 0;
        Color pressedColor = 0;

        StateIndicator():color(0) {
            animation.Duration = 150;
        }

        void setState(IndicatorState state);

        __declspec(property(put = setState)) IndicatorState State;

        virtual void onUpdate(uint64_t time) override {
            animation.update(time);
        }

        inline const Color& getColor() {
            return color;
        }

        inline void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        virtual void onDraw(Canvas& canvas);

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
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