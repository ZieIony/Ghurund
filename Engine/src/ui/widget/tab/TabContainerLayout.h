#pragma once

#include "Tab.h"

#include "core/ScopedPointer.h"
#include "ui/adapter/AdapterView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class Theme;

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
        TabContainerVerticalBottomLayout(Theme& theme);

        inline ColorView* getSeparator() {
            return separator;
        }

        __declspec(property(get = getSeparator)) ColorView* Separator;
    };

}