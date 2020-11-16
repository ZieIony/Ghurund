#pragma once

#include "ToolbarAdapter.h"

#include "core/ScopedPointer.h"
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
        ScopedPointer<RecyclerView<MenuItem*>> recyclerView;

    public:
        ToolbarLayout(Theme& theme):theme(theme) {}

        virtual void init() override;

        inline RecyclerView<MenuItem*>* getRecyclerView() {
            return recyclerView;
        }

        __declspec(property(get = getRecyclerView)) RecyclerView<MenuItem*>* RecyclerView;
    };
}