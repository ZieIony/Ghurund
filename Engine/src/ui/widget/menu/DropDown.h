#pragma once

#include "DropDownLayout.h"
#include "ui/Theme.h"
#include "ui/control/ClickableView.h"

namespace Ghurund::UI {
    class DropDown:public ClickableView {
    private:
        DropDownLayout* layout;

    public:
        DropDown(DropDownLayout* layout):layout(layout) {
            Child = layout->Root;
        }

        inline Control* getContent() {
            return layout->Content;
        }

        inline void setContent(Control* control) {
            layout->Content = control;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;

        virtual void onStateChanged() override {
            layout->onStateChanged(*this);
        }
    };
}