#pragma once

#include "ButtonLayout.h"
#include "ui/control/StackLayout.h"
#include "ui/control/ClickableView.h"
#include "ui/mixin/ImageMixin.h"
#include "ui/mixin/BackgroundMixin.h"
#include "ui/mixin/BorderMixin.h"
#include "ui/mixin/PaddingMixin.h"

namespace Ghurund::UI {

    class ImageButtonLayout:public ButtonLayout, public BackgroundLayoutMixin, public BorderLayoutMixin, public ImageLayoutMixin, public PaddingLayoutMixin {
    private:
        StackLayout* stack;
        Theme& theme;

    public:
        ImageButtonLayout(Theme& theme):theme(theme) {}

        ~ImageButtonLayout() {
            stack->release();
        }

        virtual void init() override;

        virtual void onStateChanged(Control& control) override;
    };

}