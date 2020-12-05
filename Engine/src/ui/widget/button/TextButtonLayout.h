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
        SharedPointer<StackLayout> stack;

    protected:
        SharedPointer<ClickResponseView> clickResponseView;

    public:
        virtual void init() override;

        virtual void onThemeChanged(Control& control) override;

        virtual void onStateChanged(Control& control) override;
    };

    class TextButtonFlatLayout:public TextButtonLayout {
    public:
        virtual void onStateChanged(Control& control) override;
    };

    class TextButtonAccentLayout:public TextButtonLayout {
    public:
        virtual void onThemeChanged(Control& control) override;

        virtual void onStateChanged(Control& control) override;
    };

}