#pragma once

#include "ControlContainer.h"
#include "MouseEvents.h"

namespace Ghurund::UI {
    class ClickableControl:public ControlContainer {
    private:
        bool hovered = false;
        MousePressed buttons;
        Event<Control, MousePressedEventArgs> onPressed = Event<Control, MousePressedEventArgs>(*this);
        Event<Control, MouseClickedEventArgs> onClicked = Event<Control, MouseClickedEventArgs>(*this);

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<ClickableControl>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ClickableControl))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual bool onKeyEvent(const KeyEventArgs& event) override;

        virtual bool onMouseMotionEvent(const Ghurund::Input::MouseMotionEventArgs& event) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

    public:
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

        inline Event<Control, MousePressedEventArgs>& getPressed() {
            return onPressed;
        }

        __declspec(property(get = getPressed)) Event<Control, MousePressedEventArgs>& Pressed;

        inline Event<Control, MouseClickedEventArgs>& getClicked() {
            return onClicked;
        }

        __declspec(property(get = getClicked)) Event<Control, MouseClickedEventArgs>& Clicked;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}