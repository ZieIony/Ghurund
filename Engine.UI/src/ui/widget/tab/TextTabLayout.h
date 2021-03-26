#pragma once

#include "Tab.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/SelectableView.h"

namespace Ghurund::UI {
    class Theme;

    class TextTabLayout:public TabLayout {
    private:
        Theme& theme;
        StackLayout* stack;

    public:
        TextTabLayout(Theme& theme);

        ~TextTabLayout() {
            stack->release();
        }

        void onStateChanged(Control& control);
    };
}