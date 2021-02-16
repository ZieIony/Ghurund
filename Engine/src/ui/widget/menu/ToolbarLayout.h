#pragma once

#include "ToolbarAdapter.h"

#include "core/SharedPointer.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class ToolbarLayout:public WidgetLayout {
    protected:
        SharedPointer<RecyclerView> recyclerView;

    public:
        ToolbarLayout() {}

        ToolbarLayout(Control* control) {
            recyclerView = ghnew Ghurund::UI::RecyclerView();
            recyclerView->PreferredSize.height = PreferredSize::Height::WRAP;
            recyclerView->LayoutManager = ghnew HorizontalLayoutManager();
            Root = recyclerView;
        }

        inline RecyclerView* getRecyclerView() {
            return recyclerView;
        }

        __declspec(property(get = getRecyclerView)) RecyclerView* RecyclerView;
    };
}