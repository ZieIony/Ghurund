#pragma once

#include "ControlContainer.h"

namespace Ghurund::UI {
    class ClickableControl:public ControlContainer {
    private:
        bool hovered = false;
        MousePressed buttons;

    protected:
        virtual bool onKeyEvent(const KeyEventArgs& event) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        Event<Control, MousePressedEventArgs> pressed = *this;
        Event<Control, MouseClickedEventArgs> clicked = *this;

        ClickableControl() {
            Focusable = true;
        }

        inline bool isHovered() const {
            return hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;
        
        inline const MousePressed& isPressed() const {
            return buttons;
        }

        __declspec(property(get = isPressed)) const MousePressed& Pressed;

        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ClickableControl::GET_TYPE();
    };
}