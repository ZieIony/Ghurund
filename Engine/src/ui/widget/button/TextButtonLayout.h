#pragma once

#include "ButtonLayout.h"
#include "ui/control/ClickableView.h"
#include "ui/layout/StackLayout.h"
#include "ui/mixin/TextMixin.h"
#include "ui/mixin/BackgroundMixin.h"
#include "ui/mixin/BorderMixin.h"
#include "ui/mixin/PaddingMixin.h"

namespace Ghurund::UI {

    class TextButtonLayout:public ButtonLayout, public BackgroundLayoutMixin, public BorderLayoutMixin, public TextLayoutMixin, public PaddingLayoutMixin {
    private:
        StackLayout* stack = nullptr;

    protected:
        Theme& theme;

    public:
        TextButtonLayout(Theme& theme):theme(theme) {}

        ~TextButtonLayout() {
            stack->release();
        }

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