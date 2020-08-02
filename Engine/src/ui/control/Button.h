#pragma once

#include "ui/gdi/GdiFont.h"

namespace Ghurund {
    class Button :public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Button);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Button>();

        bool pressed = false;

    public:
        inline void setContent(Control* control) {
            Child = control;
        }

        inline Control* getContent() {
            return Child;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;

        inline bool isPressed() const {
            return pressed;
        }

        __declspec(property(get = isPressed)) bool Pressed;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            return onMouseButtonEvent(event);
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

        inline static const Ghurund::Type& TYPE = TypeBuilder<Button>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(ControlContainer::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}