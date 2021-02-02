#pragma once

#include "ui/control/ClickableView.h"
#include "ui/layout/StackLayout.h"
#include "ui/mixin/TextMixin.h"
#include "ui/mixin/BackgroundMixin.h"
#include "ui/mixin/BorderMixin.h"
#include "ui/mixin/PaddingMixin.h"
#include "ui/widget/Layout.h"

namespace Ghurund::UI {
    class ButtonLayout:public WidgetLayout {
    protected:
        ClickableView* clickableView = nullptr;

    public:
        ButtonLayout() {}

        ButtonLayout(Control* layout) {}

        ~ButtonLayout() {
            if (clickableView)
                clickableView->release();
        }

        inline ClickableView* getClickableView() {
            return clickableView;
        }

        __declspec(property(get = getClickableView)) ClickableView* ClickableView;
    };

}