#pragma once

#include "ui/Animation.h"
#include "ui/control/ColorView.h"

namespace Ghurund::UI {
    enum class IndicatorState {
        NONE, FOCUSED, PRESSED
    };

    class StateIndicator:public ColorView {
    private:
        static const Ghurund::UI::Style& DEFAULT_STYLE;

    protected:
        static const Ghurund::Type& GET_TYPE();

        Animation animation;
        IndicatorState state = IndicatorState::NONE;
        Ghurund::UI::Color prevColor = 0;

    public:
        Ghurund::UI::Color focusedColor = 0;
        Ghurund::UI::Color pressedColor = 0;

        StateIndicator() {
            style = &DEFAULT_STYLE;
            animation.Duration = 150;
        }

        void setState(IndicatorState state);

        __declspec(property(put = setState)) IndicatorState State;

        virtual void onUpdate(uint64_t time) override {
            animation.update(time);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class StateIndicatorStyle:public Style {
    public:
        virtual void onThemeChanged(Control& control) const override;
    };
}