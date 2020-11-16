#pragma once

#include "MenuBarAdapter.h"

#include "core/ScopedPointer.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class MenuBarLayout:public WidgetLayout {
    protected:
        ScopedPointer<RecyclerView<MenuItem*>> recyclerView;
        Theme& theme;

    public:
        MenuBarLayout(Theme& theme):theme(theme) {}

        virtual void init() override {
            recyclerView = ghnew Ghurund::UI::RecyclerView<MenuItem*>();
            recyclerView->PreferredSize.height = PreferredSize::Height::WRAP;
            recyclerView->LayoutManager = ghnew HorizontalLayoutManager();
            recyclerView->Adapters.add(ghnew ButtonMenuBarAdapter(theme));
            root = recyclerView;
        }

        inline RecyclerView<MenuItem*>* getAdapterView() {
            return recyclerView;
        }

        __declspec(property(get = getAdapterView)) RecyclerView<MenuItem*>* RecyclerView;
    };

    class MenuBarWithBackgroundLayout:public MenuBarLayout {
    protected:
        ScopedPointer<StackLayout> stack;
        ScopedPointer<ColorView> backgroundView;

    public:
        MenuBarWithBackgroundLayout(Theme& theme):MenuBarLayout(theme) {}

        virtual void init() override;

        inline ColorView* getBackgroundView() {
            return backgroundView;
        }

        __declspec(property(get = getBackgroundView)) ColorView* BackgroundView;
    };
}