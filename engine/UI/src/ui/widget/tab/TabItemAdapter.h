#pragma once

#include "Tab.h"
#include "ui/adapter/ItemAdapter.h"

namespace Ghurund::UI {
    class TabContainer;
    class Theme;

    class TabItemAdapter:public ItemAdapter {
    public:
        virtual Tab* makeControl() const;

        virtual void bind(Control& control, size_t position) const;

    };

    class TextTabItemAdapter:public TabItemAdapter {
    public:
        virtual void bind(Control& control, size_t position) const;
    };
}