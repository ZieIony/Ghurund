#pragma once

#include "Tab.h"
#include "ui/control/StackLayout.h"
#include "ui/control/SelectableView.h"
#include "ui/mixin/TextMixin.h"
#include "ui/mixin/BackgroundMixin.h"
#include "ui/mixin/BorderMixin.h"
#include "ui/mixin/PaddingMixin.h"

namespace Ghurund::UI {
    class Theme;

    class TextTabLayout:public TabLayout, public BackgroundLayoutMixin, public BorderLayoutMixin, public TextLayoutMixin, public PaddingLayoutMixin {
    private:
        StackLayout* stack;

    public:
        TextTabLayout() {
            stack = ghnew StackLayout();
            paddingContainer->Child = textView;
            stack->PreferredSize.width = PreferredSize::Width::WRAP;
            stack->PreferredSize.height = PreferredSize::Height::WRAP;
            stack->Children = { backgroundView, border, paddingContainer };
            selectableView = ghnew Ghurund::UI::SelectableView();
            selectableView->Child = stack;
            root = selectableView;
        }

        ~TextTabLayout() {
            stack->release();
        }
    };

    class TextTabStyle:public Ghurund::UI::StyleWithLayout<Tab, TabLayout> {
    public:
        TextTabStyle(Theme& theme);

        virtual void apply(Tab& tab) const override;

        virtual void onStateChanged(Tab& tab) const override;

        virtual TextTabLayout* makeLayout() const override;
    };
}