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
        Paint paint;

    protected:
        static const Ghurund::Type& GET_TYPE();

        Animation animation;
        IndicatorState state = IndicatorState::NONE;
        Ghurund::UI::Color prevColor = 0;

    public:
        Ghurund::UI::Color idleColor = 0;
        Ghurund::UI::Color focusedColor = 0;
        Ghurund::UI::Color pressedColor = 0;

        StateIndicator() {
            animation.Duration = 150;
        }

        void setState(IndicatorState state);

        __declspec(property(put = setState)) IndicatorState State;

        virtual void onUpdate(uint64_t time) override {
            animation.update(time);
        }

        inline const Color& getColor() {
            return paint.Color;
        }

        inline void setColor(const Color& color) {
            paint.Color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        virtual void onDraw(Canvas& canvas) {
            if (!paint.Color)
                return;
            canvas.fillRect(0, 0, Size.width, Size.height, paint);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
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