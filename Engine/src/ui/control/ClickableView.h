#pragma once

#include "HoverableView.h"

namespace Ghurund::UI {
    class MousePressed {
        bool pressed[4] = { false, false, false, false };

    public:
        operator bool() const {
            return pressed[0] || pressed[1] || pressed[2] || pressed[3];
        }

        bool& operator[](MouseButton button) {
            return pressed[(unsigned int)button];
        }

        const bool& operator[](MouseButton button) const {
            return pressed[(unsigned int)button];
        }
    };

    class ClickableView:public HoverableView {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ClickableView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ClickableView>();

        MousePressed buttons;
        Event<Control, MouseButton> onPressed = Event<Control, MouseButton>(*this);
        Event<Control, MouseButton> onClicked = Event<Control, MouseButton>(*this);

    public:
        inline const MousePressed& isPressed() const {
            return buttons;
        }

        __declspec(property(get = isPressed)) const MousePressed& Pressed;

        inline Event<Control, MouseButton>& getOnPressed() {
            return onPressed;
        }

        __declspec(property(get = getOnPressed)) Event<Control, MouseButton>& OnPressed;

        inline Event<Control, MouseButton>& getOnClicked() {
            return onClicked;
        }

        __declspec(property(get = getOnClicked)) Event<Control, MouseButton>& OnClicked;

        bool dispatchKeyEvent(const KeyEventArgs& event) {
            if (event.Key == VK_SPACE || event.Key == VK_RETURN) {
                if (event.Action == KeyAction::DOWN) {
                    buttons[MouseButton::VIRTUAL] = true;
                    onStateChanged();
                    onPressed(MouseButton::VIRTUAL);
                    return true;
                } else if(event.Action == KeyAction::UP){
                    buttons[MouseButton::VIRTUAL] = false;
                    onStateChanged();
                    onClicked(MouseButton::VIRTUAL);
                    return true;
                }
            }
            return __super::dispatchKeyEvent(event);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            bool result = false;
            if (event.Action == MouseAction::DOWN && !buttons[event.Button]) {
                buttons[event.Button] = true;
                onStateChanged();
                result = onPressed(event.Button);
            } else if (event.Action == MouseAction::UP && buttons[event.Button]) {
                buttons[event.Button] = false;
                onStateChanged();
                result = onClicked(event.Button);
            }
            return result | Control::dispatchMouseButtonEvent(event);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ClickableView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}