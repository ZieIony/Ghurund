#pragma once

#include "TabItemAdapter.h"
#include "core/SharedPointer.h"
#include "ui/adapter/AdapterChildrenProvider.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
    class TabContainer:public ContentWidget {
    private:
        size_t selectedPosition = 0;
        Tab* selectedTab = nullptr;
        List<TabItem*> tabs;
        Ghurund::UI::RecyclerView* tabLayout = nullptr;
        AdapterChildrenProvider<TabItem*, Tab>* provider;

        typedef SingleAdapterChildrenProvider<TabItem*, Tab, TabItemAdapter> TabChildrenProvider;

    protected:
        virtual void bind() override {
            __super::bind();
            tabLayout = (Ghurund::UI::RecyclerView*)find("tabs");
            provider = ghnew TabChildrenProvider();
            tabLayout->ChildrenProvider = std::unique_ptr<ChildrenProvider>(provider);
        }

    public:
        class LayoutVerticalBottom;

        TabContainer();

        ~TabContainer();

        inline List<TabItem*>& getTabs() {
            return provider->ItemSource.Items;
        }

        inline void setTabs(const List<TabItem*>& tabs) {
            this->tabs.clear();
            this->tabs.addAll(tabs);
        }

        __declspec(property(get = getTabs, put = setTabs)) List<TabItem*>& Tabs;

        inline void setSelectedPosition(size_t position) {
            if (selectedTab)
                selectedTab->Selected = false;
            this->selectedPosition = position;
            if (tabLayout->Children.Size > position) {
                setPointer(selectedTab, (Tab*)tabLayout->Children[position]);
                selectedTab->Selected = true;
            }
            TabItem* tab = tabs[position];
            //content.Value = SharedPointer<Control>(tab->content);
            tab->content->invalidate();
        }

        inline size_t getSelectedPosition() const {
            return selectedPosition;
        }

        __declspec(property(get = getSelectedPosition, put = setSelectedPosition)) size_t SelectedPosition;
    };
}