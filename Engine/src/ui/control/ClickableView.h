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

    class MousePressedEventArgs:public MouseEventArgs {
    private:
        MouseButton button;

    public:
        MousePressedEventArgs(const XMINT2& pos, MouseButton button, time_t time):MouseEventArgs(pos, time, true) {
            this->button = button;
        }

        MouseButton getButton() const {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;
    };

    class MouseClickedEventArgs:public MouseEventArgs {
    private:
        MouseButton button;

    public:
        MouseClickedEventArgs(const XMINT2& pos, MouseButton button, time_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->button = button;
        }

        MouseButton getButton() const {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;
    };

    class ClickableView:public HoverableView {
    private:
        MousePressed buttons;
        Event<Control, MousePressedEventArgs> onPressed = Event<Control, MousePressedEventArgs>(*this);
        Event<Control, MouseClickedEventArgs> onClicked = Event<Control, MouseClickedEventArgs>(*this);

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ClickableView>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ClickableView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

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

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            bool result = __super::dispatchMouseMotionEvent(event);
            return result || buttons;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}