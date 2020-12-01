#pragma once

#include "ButtonLayout.h"
#include "ui/control/ClickableView.h"
#include "ui/layout/StackLayout.h"
#include "ui/mixin/ImageMixin.h"
#include "ui/mixin/BackgroundMixin.h"
#include "ui/mixin/BorderMixin.h"
#include "ui/mixin/PaddingMixin.h"
#include "ui/widget/ClickResponseView.h"

namespace Ghurund::UI {

    class ImageButtonLayout:public ButtonLayout, public BackgroundLayoutMixin, public BorderLayoutMixin, public ImageLayoutMixin, public PaddingLayoutMixin {
    private:
        SharedPointer<StackLayout> stack;

    protected:
        Theme& theme;
        SharedPointer<ClickResponseView> clickResponseView;

    public:
        ImageButtonLayout(Theme& theme):theme(theme) {}

        virtual void init() override;

        virtual void onStateChanged(Control& control) override;
    };

    class ImageButtonFlatLayout:public ImageButtonLayout {
    public:
        ImageButtonFlatLayout(Theme& theme):ImageButtonLayout(theme) {}

        virtual void onStateChanged(Control& control) override;
    };

}