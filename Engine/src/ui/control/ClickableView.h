#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    class ClickableView :public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ClickableView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ClickableView>();

        bool pressed[3] = { false,false,false };
        bool hovered = false;
        Event<Control, MouseButton> onClicked;

    public:
        inline bool isPressed() const {
            return pressed[0] || pressed[1] || pressed[2];
        }

        __declspec(property(get = isPressed)) bool Pressed;

        inline bool isHovered() const {
            return hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;

        Event<Control, MouseButton>& getOnClicked() {
            return onClicked;
        }

        __declspec(property(get = getOnClicked)) Event<Control, MouseButton>& OnClicked;

        virtual void measure() override {
            __super::measure();
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            return onMouseButtonEvent(event);
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            return onMouseMotionEvent(event);
        }

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override {
            if (event.Action == MouseAction::DOWN && !pressed[(unsigned int)event.Button]) {
                pressed[(unsigned int)event.Button] = true;
                onStateChanged(*this);
            } else if (event.Action == MouseAction::UP && pressed[(unsigned int)event.Button]) {
                pressed[(unsigned int)event.Button] = false;
                onStateChanged(*this);
                onClicked(*this, event.Button);
            }
            return true;
        }

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override {
            if (canReceiveEvent(event) && !hovered) {
                hovered = true;
                onStateChanged(*this);
            } else if (!canReceiveEvent(event) && hovered) {
                hovered = false;
                onStateChanged(*this);
            }
            return false;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ClickableView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static ClickableView* inflate(LayoutInflater& inflater, json& json) {
            ClickableView* button = ghnew ClickableView();
            inflater.loadChild(button, json);
            inflater.loadControl(button, json);
            return button;
        }
    };
}