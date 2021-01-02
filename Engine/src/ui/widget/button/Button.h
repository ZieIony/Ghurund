#pragma once

#include "ButtonLayout.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class Button:public Widget<ButtonLayout> {
    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Button))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        Button(ButtonLayout* layout):Widget(layout) {
            Focusable = true;
            Layout.ClickableView->OnStateChanged.add(OnStateChanged);
        }

        inline bool isHovered() const {
            return Layout.ClickableView->Hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;

        inline const MousePressed& isPressed() const {
            return Layout.ClickableView->Pressed;
        }

        __declspec(property(get = isPressed)) MousePressed& Pressed;

        inline Event<Control, MouseClickedEventArgs>& getOnClicked() {
            return Layout.ClickableView->OnClicked;
        }

        __declspec(property(get = getOnClicked)) Event<Control, MouseClickedEventArgs>& OnClicked;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}