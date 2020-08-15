#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    class ClickableView :public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ClickableView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ClickableView>();

        bool pressed = false;
        bool hovered = false;

    public:
        inline bool isPressed() const {
            return pressed;
        }

        __declspec(property(get = isPressed)) bool Pressed;

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
            if (event.Action == MouseAction::DOWN && !pressed) {
                pressed = true;
                onStateChanged(*this);
            } else if (event.Action == MouseAction::UP && pressed) {
                pressed = false;
                onStateChanged(*this);
            }
            return true;
        }

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override {
            bool in = event.Position.x >= Position.x && event.Position.x <= Position.x + Size.x &&
                event.Position.y >= Position.y && event.Position.y <= Position.y + Size.y;

            if (in && !hovered) {
                hovered = true;
                onStateChanged(*this);
            } else if (!in && hovered) {
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