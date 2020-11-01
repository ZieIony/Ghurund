#pragma once

#include "ButtonLayout.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class Button:public Widget2<ButtonLayout> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Button);

    public:
        Button(ButtonLayout* layout):Widget2(layout) {
            Focusable = true;
        }

        inline bool isHovered() const {
            return Layout.ClickableView->Hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;

        inline const MousePressed& isPressed() const {
            return Layout.ClickableView->Pressed;
        }

        __declspec(property(get = isPressed)) MousePressed& Pressed;

        inline Event<Control, MouseButton>& getOnClicked() {
            return Layout.ClickableView->OnClicked;
        }

        __declspec(property(get = getOnClicked)) Event<Control, MouseButton>& OnClicked;

        inline static const Ghurund::Type& TYPE = TypeBuilder<Button>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}