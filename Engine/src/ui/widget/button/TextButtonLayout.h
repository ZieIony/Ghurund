#pragma once

#include "ButtonLayout.h"
#include "ui/control/ClickableView.h"
#include "ui/layout/StackLayout.h"
#include "ui/mixin/TextMixin.h"
#include "ui/mixin/BackgroundMixin.h"
#include "ui/mixin/BorderMixin.h"
#include "ui/mixin/PaddingMixin.h"
#include "ui/widget/ClickResponseView.h"

namespace Ghurund::UI {

    class TextButtonLayout:public ButtonLayout, public BackgroundLayoutMixin, public BorderLayoutMixin, public TextLayoutMixin, public PaddingLayoutMixin {
    private:
        ScopedPointer<StackLayout> stack;

    protected:
        Theme& theme;

    public:
        TextButtonLayout(Theme& theme):theme(theme) {}

        virtual void init() override;

        virtual void onStateChanged(Control& control) override;
    };

    class TextButtonFlatLayout:public TextButtonLayout {
    public:
        TextButtonFlatLayout(Theme& theme):TextButtonLayout(theme) {}

        virtual void onStateChanged(Control& control) override;
    };

    class TextButtonAccentLayout:public TextButtonLayout {
    public:
        TextButtonAccentLayout(Theme& theme):TextButtonLayout(theme) {}

        virtual void onStateChanged(Control& control) override;
    };

}