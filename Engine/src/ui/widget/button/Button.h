#pragma once

#include "ButtonLayout.h"
#include "ui/control/ClickableControl.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
    class Button:public ContentWidget<ButtonLayout> {
    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        inline bool isHovered() const {
            return Layout->Clickable->Hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;

        inline const MousePressed& isPressed() const {
            return Layout->Clickable->Pressed;
        }

        __declspec(property(get = isPressed)) MousePressed& Pressed;

        inline Event<Control, MouseClickedEventArgs>& getClicked() {
            return Layout->Clickable->Clicked;
        }

        __declspec(property(get = getClicked)) Event<Control, MouseClickedEventArgs>& Clicked;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}