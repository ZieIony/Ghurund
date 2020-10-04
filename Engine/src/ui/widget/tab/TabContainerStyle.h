#pragma once

#include "TabContainer.h"
#include "TabContainerLayout.h"

namespace Ghurund::UI {
    class TabContainerStyle:public StyleWithLayout<TabContainer, TabContainerLayout> {
    public:
        TabContainerStyle(Theme& theme);

        virtual void apply(TabContainer& tabLayout) const override;

        virtual TabContainerLayout* makeLayout() const override {
            return ghnew TabContainerVerticalBottomLayout();
        }
    };
}