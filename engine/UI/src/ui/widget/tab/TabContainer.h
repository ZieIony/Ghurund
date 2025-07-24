#pragma once

#include "TabItemAdapter.h"
#include "core/object/IntrusivePointer.h"
#include "ui/adapter/AdapterLayout.h"
//#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
    class TabContainer:public ContentWidget {
    private:
        size_t selectedPosition = 0;
        Tab* selectedTab = nullptr;
        List<TabItem*> tabs;
        Ghurund::UI::AdapterLayout* tabLayout = nullptr;

    protected:
        virtual void bind() override {
            __super::bind();
            tabLayout = (Ghurund::UI::AdapterLayout*)find("tabs");
            //provider = ghnew TabChildrenProvider();
            //tabLayout->ControlProvider = std::unique_ptr<ControlProvider>(provider);
        }

    public:
        class LayoutVerticalBottom;

        TabContainer();

        ~TabContainer();

        inline void setTabs(const List<TabItem*>& tabs) {
            this->tabs.clear();
            this->tabs.addAll(tabs);
        }

        __declspec(property(put = setTabs)) List<TabItem*>& Tabs;

        inline void setSelectedPosition(size_t position) {
            if (selectedTab)
                selectedTab->Selected = false;
            this->selectedPosition = position;
            if (tabLayout->Children.Size > position) {
                setPointer(selectedTab, (Tab*)tabLayout->Children[position].control.get());
                selectedTab->Selected = true;
            }
            TabItem* tab = tabs[position];
            //content.Value = IntrusivePointer<Control>(tab->content);
            tab->content->requestLayout();
        }

        inline size_t getSelectedPosition() const {
            return selectedPosition;
        }

        __declspec(property(get = getSelectedPosition, put = setSelectedPosition)) size_t SelectedPosition;
    };
}