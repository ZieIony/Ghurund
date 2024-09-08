#pragma once

#include "core/math/Size.h"
#include "core/state/State.h"
#include "MouseEvents.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class InteractionHandler {
    private:
        Control& owner;
        MousePressed buttons;
        Ghurund::Core::FloatSize size = { 0, 0 };

        EventHandler<Control> stateChangedHandler = [this](Control& control) {
            isFocused = (bool)control.Focused;
            return true;
        };

        EventHandler<EventConsumer, KeyEventArgs> keyEventHandler = [this](EventConsumer& control, const KeyEventArgs& event) {
            return onKeyEvent(event);
        };

        EventHandler<EventConsumer, MouseButtonEventArgs> mouseButtonEventHandler = [this](EventConsumer& control, const MouseButtonEventArgs& event) {
            return onMouseButtonEvent(event);
        };

        EventHandler<EventConsumer, MouseMotionEventArgs> mouseMotionEventHandler = [this](EventConsumer& control, const MouseMotionEventArgs& event) {
            return onMouseMotionEvent(event);
        };

        bool onKeyEvent(const KeyEventArgs& event);

        bool onMouseButtonEvent(const MouseButtonEventArgs& event);

        bool onMouseMotionEvent(const MouseMotionEventArgs& event);

        EventHandler<InteractionHandler, MousePressedEventArgs> pressHandler = [this](InteractionHandler&, const MousePressedEventArgs& args) {
            owner.Parent->CapturedChild = &owner;
            owner.requestFocus();
            return true;
        };

        EventHandler<InteractionHandler> cancelHandler = [this](InteractionHandler&) {
            owner.Parent->CapturedChild = nullptr;
            return true;
        };

        EventHandler<InteractionHandler, MouseClickedEventArgs> clickHandler = [this](InteractionHandler&, const MouseClickedEventArgs& args) {
            owner.Parent->CapturedChild = nullptr;
            return true;
        };

    public:
        InteractionHandler(Control& owner):owner(owner) {
            owner.stateChanged += stateChangedHandler;
            owner.keyEvent += keyEventHandler;
            owner.mouseButtonEvent += mouseButtonEventHandler;
            owner.mouseMotionEvent += mouseMotionEventHandler;
            pressed += pressHandler;
            canceled += cancelHandler;
            clicked += clickHandler;
        }

        ~InteractionHandler() {
            owner.stateChanged -= stateChangedHandler;
            owner.keyEvent -= keyEventHandler;
            owner.mouseButtonEvent -= mouseButtonEventHandler;
            owner.mouseMotionEvent -= mouseMotionEventHandler;
        }

        State<bool> isHovered = false, isFocused = false, isPressed = false;
        Event<InteractionHandler, MousePressedEventArgs> pressed = *this;
        Event<InteractionHandler> canceled = *this;
        Event<InteractionHandler, MouseClickedEventArgs> clicked = *this;
    };
}