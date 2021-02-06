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

        ToolbarLayout(Control* control) {}

        virtual void init() override;

        inline RecyclerView* getRecyclerView() {
            return recyclerView;
        }

        __declspec(property(get = getRecyclerView)) RecyclerView* RecyclerView;
    };
}