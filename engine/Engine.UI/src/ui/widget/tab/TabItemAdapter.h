#pragma once

#include "Tab.h"
#include "ui/adapter/ItemAdapter.h"

namespace Ghurund::UI {
    class TabContainer;
    class Theme;

    class TabItemAdapter:public ItemAdapter<TabItem*, Tab> {
    public:
        virtual Tab* makeControl() const;

        virtual void bind(Tab& control, TabItem* const& item, size_t position) const;

    };

    class TextTabItemAdapter:public TabItemAdapter {
    public:
        virtual void bind(Tab& control, TabItem* const& item, size_t position) const;
    };
}