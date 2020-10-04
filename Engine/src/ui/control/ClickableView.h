#pragma once

#include "HoverableView.h"

namespace Ghurund::UI {
    class MousePressed {
        bool pressed[3] = { false, false, false };

    public:
        operator bool() const {
            return pressed[0] || pressed[1] || pressed[2];
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
        Event<Control, MouseButton> onClicked = Event<Control, MouseButton>(*this);

    public:
        inline const MousePressed& isPressed() const {
            return buttons;
        }

        __declspec(property(get = isPressed)) const MousePressed& Pressed;

        Event<Control, MouseButton>& getOnClicked() {
            return onClicked;
        }

        __declspec(property(get = getOnClicked)) Event<Control, MouseButton>& OnClicked;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            bool result = false;
            if (event.Action == MouseAction::DOWN && !buttons[event.Button]) {
                buttons[event.Button] = true;
                onStateChanged();
                result = true;
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