#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    class ClickableView :public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ClickableView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ClickableView>();

        bool pressed[3] = { false,false,false };
        Event<Control, MouseButton> onClicked = Event<Control, MouseButton>(*this);

    public:
        inline bool isPressed() const {
            return pressed[0] || pressed[1] || pressed[2];
        }

        __declspec(property(get = isPressed)) bool Pressed;

        Event<Control, MouseButton>& getOnClicked() {
            return onClicked;
        }

        __declspec(property(get = getOnClicked)) Event<Control, MouseButton>& OnClicked;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            return onMouseButtonEvent(event);
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            return onMouseMotionEvent(event);
        }

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override {
            if (event.Action == MouseAction::DOWN && !pressed[(unsigned int)event.Button]) {
                pressed[(unsigned int)event.Button] = true;
                onStateChanged();
            } else if (event.Action == MouseAction::UP && pressed[(unsigned int)event.Button]) {
                pressed[(unsigned int)event.Button] = false;
                onStateChanged();
                onClicked(event.Button);
            }
            return true;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ClickableView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static ClickableView* inflate(LayoutInflater& inflater, json& json) {
            ClickableView* clickableView = ghnew ClickableView();
            inflater.loadChild(clickableView, json);
            inflater.loadControl(clickableView, json);
            return clickableView;
        }
    };
}