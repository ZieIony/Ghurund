#pragma once

#include "ToolbarAdapter.h"

#include "core/SharedPointer.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class Theme;

    class ToolbarLayout:public WidgetLayout {
    protected:
        Theme& theme;
        SharedPointer<RecyclerView> recyclerView;

    public:
        ToolbarLayout(Theme& theme):theme(theme) {}

        ToolbarLayout(Control* control):theme(theme) {}

        virtual void init() override;

        inline RecyclerView* getRecyclerView() {
            return recyclerView;
        }

        __declspec(property(get = getRecyclerView)) RecyclerView* RecyclerView;
    };
}