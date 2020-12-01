#pragma once

#include "Tab.h"

#include "ui/adapter/RecyclerView.h"
#include "ui/control/ColorView.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class Theme;

    class TabContainerLayout:public Ghurund::UI::WidgetLayout {
    protected:
        SharedPointer<ControlContainer> container;
        SharedPointer<RecyclerView<TabItem*, Tab>> tabContainer;

    public:
        virtual ~TabContainerLayout() = 0 {}

        inline ControlContainer* getContainer() {
            return container;
        }

        __declspec(property(get = getContainer)) ControlContainer* Container;

        inline RecyclerView<TabItem*, Tab>* getTabContainer() {
            return tabContainer;
        }

        __declspec(property(get = getTabContainer)) RecyclerView<TabItem*, Tab>* TabContainer;
    };

    class TabContainerVerticalBottomLayout:public TabContainerLayout {
    protected:
        SharedPointer<ColorView> separator;
        Theme& theme;

    public:
        TabContainerVerticalBottomLayout(Theme& theme):theme(theme) {}

        virtual void init() override;

        inline ColorView* getSeparator() {
            return separator;
        }

        __declspec(property(get = getSeparator)) ColorView* Separator;
    };

}