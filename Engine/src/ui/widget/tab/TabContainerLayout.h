#pragma once

#include "Tab.h"
#include "core/ScopedPointer.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/control/AdapterView.h"
#include "ui/control/LinearLayout.h"
#include "ui/control/ColorView.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class TabContainerLayout:public Ghurund::UI::Layout {
    protected:
        ScopedPointer<ControlContainer> container;
        ScopedPointer<AdapterView<TabItem*, Tab>> tabContainer;

    public:
        virtual ~TabContainerLayout() = 0 {}

        inline ControlContainer* getContainer() {
            return container;
        }

        __declspec(property(get = getContainer)) ControlContainer* Container;

        inline AdapterView<TabItem*, Tab>* getTabContainer() {
            return tabContainer;
        }

        __declspec(property(get = getTabContainer)) AdapterView<TabItem*, Tab>* TabContainer;
    };

    class TabContainerVerticalBottomLayout:public TabContainerLayout {
    protected:
        ScopedPointer<ColorView> separator;

    public:
        TabContainerVerticalBottomLayout() {
            VerticalLayout* column = ghnew VerticalLayout();
            container = ghnew ControlContainer();
            container->PreferredSize.width = PreferredSize::Width::FILL;
            container->PreferredSize.height = PreferredSize::Height::FILL;
            separator = ghnew ColorView();
            tabContainer = ghnew AdapterView<TabItem*, Tab>();
            tabContainer->PreferredSize.height = PreferredSize::Height::WRAP;
            tabContainer->LayoutManager = ghnew HorizontalLayoutManager<TabItem*, Tab>();
            column->Children = { container, separator, tabContainer };
            root = column;
        }

        inline ColorView* getSeparator() {
            return separator;
        }

        __declspec(property(get = getSeparator)) ColorView* Separator;
    };

}