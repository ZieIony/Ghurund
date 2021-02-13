#pragma once

#include "ButtonLayout.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
    class Button:public ContentWidget<ButtonLayout> {
    protected:
        static const Ghurund::Type& GET_TYPE();

        virtual void onLayoutChanged() override;

    public:
        inline bool isHovered() const {
            return Layout->ClickableControl->Hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;

        inline const MousePressed& isPressed() const {
            return Layout->ClickableControl->Pressed;
        }

        __declspec(property(get = isPressed)) MousePressed& Pressed;

        inline Event<Control, MouseClickedEventArgs>& getOnClicked() {
            return Layout->ClickableControl->OnClicked;
        }

        __declspec(property(get = getOnClicked)) Event<Control, MouseClickedEventArgs>& OnClicked;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}