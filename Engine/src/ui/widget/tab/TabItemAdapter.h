#pragma once

#include "Tab.h"
#include "ui/control/ItemAdapter.h"

namespace Ghurund::UI {
    class TabContainer;
    class Theme;

    class TabItemAdapter:public ItemAdapter<TabItem*, Tab> {
    protected:
        TabContainer& tabLayout;
        Theme& theme;

    public:
        TabItemAdapter(TabContainer& tabLayout, Theme& theme):tabLayout(tabLayout), theme(theme) {}

        virtual Tab* makeControl() const;

        virtual void bind(Tab& control, TabItem* const& item, size_t position) const;

    };

    class TextTabItemAdapter:public TabItemAdapter {
    public:
        TextTabItemAdapter(TabContainer& tabContainer, Theme& theme):TabItemAdapter(tabContainer, theme) {}

        virtual void bind(Tab& control, TabItem* const& item, size_t position) const;

    };
}