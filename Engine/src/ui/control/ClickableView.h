#pragma once

#include "HoverableView.h"
#include "MouseEvents.h"

namespace Ghurund::UI {
    class ClickableView:public HoverableView {
    private:
        MousePressed buttons;
        Event<Control, MousePressedEventArgs> onPressed = Event<Control, MousePressedEventArgs>(*this);
        Event<Control, MouseClickedEventArgs> onClicked = Event<Control, MouseClickedEventArgs>(*this);

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ClickableView>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ClickableView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    protected:
        virtual bool onKeyEvent(const KeyEventArgs& event) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

    public:
        inline const MousePressed& isPressed() const {
            return buttons;
        }

        __declspec(property(get = isPressed)) const MousePressed& Pressed;

        inline Event<Control, MousePressedEventArgs>& getOnPressed() {
            return onPressed;
        }

        __declspec(property(get = getOnPressed)) Event<Control, MousePressedEventArgs>& OnPressed;

        inline Event<Control, MouseClickedEventArgs>& getOnClicked() {
            return onClicked;
        }

        __declspec(property(get = getOnClicked)) Event<Control, MouseClickedEventArgs>& OnClicked;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}