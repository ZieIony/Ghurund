#pragma once

#include "Tab.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/SelectableView.h"
#include "ui/mixin/TextMixin.h"
#include "ui/mixin/BackgroundMixin.h"
#include "ui/mixin/BorderMixin.h"
#include "ui/mixin/PaddingMixin.h"

namespace Ghurund::UI {
    class Theme;

    class TextTabLayout:public TabLayout, public BackgroundLayoutMixin, public BorderLayoutMixin, public TextLayoutMixin, public PaddingLayoutMixin {
    private:
        Theme& theme;
        StackLayout* stack;

    public:
        TextTabLayout(Theme& theme):theme(theme) {}

        ~TextTabLayout() {
            stack->release();
        }

        virtual void init() override;

        void onStateChanged(Control& control);
    };
}