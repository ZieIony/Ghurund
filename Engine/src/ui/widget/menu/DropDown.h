#pragma once

#include "DropDownLayout.h"
#include "ui/style/Theme.h"
#include "ui/control/ClickableView.h"

namespace Ghurund::UI {
    class DropDown:public Widget<DropDownLayout> {
    public:
        DropDown(DropDownLayout* layout):Widget(layout) {}

        inline Control* getContent() {
            return Layout->Content;
        }

        inline void setContent(Control* control) {
            Layout->Content = control;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;
    };
}