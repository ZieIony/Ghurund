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
        SharedPointer<ClickResponseView> clickResponseView;

    public:
        virtual void init() override;

        virtual void onThemeChanged(Control& control) override;

        virtual void onStateChanged(Control& control) override;
    };

    class ImageButtonFlatLayout:public ImageButtonLayout {
    public:
        virtual void onStateChanged(Control& control) override;
    };

}