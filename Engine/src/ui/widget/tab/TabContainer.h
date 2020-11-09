#pragma once

#include "TabItemAdapter.h"
#include "core/ScopedPointer.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"
#include "TabContainerLayout.h"

namespace Ghurund::UI {
    class TabContainer:public Widget<TabContainerLayout> {
    private:
        size_t selectedPosition = 0;
        List<TabItem*> tabs;

    public:
        class LayoutVerticalBottom;

        TabContainer(TabContainerLayout* layout);

        TabContainer(Theme& theme):TabContainer(ghnew TabContainerVerticalBottomLayout(theme)) {}

        ~TabContainer();

        inline List<TabItem*>& getTabs() {
            return tabs;
        }

        __declspec(property(get = getTabs)) List<TabItem*>& Tabs;

        inline void setSelectedPosition(size_t position) {
            if (Layout.TabContainer->Children.Size > 0) {
                Tab* tab = (Tab*)Layout.TabContainer->Children[selectedPosition];
                tab->Layout.SelectableView->Selected = false;
            }
            this->selectedPosition = position;
            if (Layout.TabContainer->Children.Size > 0) {
                Tab* tab = (Tab*)Layout.TabContainer->Children[position];
                tab->Layout.SelectableView->Selected = true;
            }
            TabItem* tab = tabs[position];
            Layout.Container->Child = tab->content;
            tab->content->invalidate();
        }

        inline size_t getSelectedPosition() const {
            return selectedPosition;
        }

        __declspec(property(get = getSelectedPosition, put = setSelectedPosition)) size_t SelectedPosition;
    };
}