#pragma once

#include "MenuBarAdapter.h"

#include "core/SharedPointer.h"
#include "ui/adapter/AdapterChildrenProvider.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class MenuBarLayout:public WidgetLayout {
    protected:
        SharedPointer<RecyclerView> recyclerView;
        ResourceContext& context;
        LayoutLoader& loader;
        Theme& theme;

    public:
        MenuBarLayout(ResourceContext& context, LayoutLoader& loader, Theme& theme):context(context), loader(loader), theme(theme) {}

        MenuBarLayout(Control* layout):context(context), loader(loader), theme(theme) {}

        virtual void init() override {
            recyclerView = ghnew Ghurund::UI::RecyclerView();
            recyclerView->PreferredSize.height = PreferredSize::Height::WRAP;
            recyclerView->LayoutManager = ghnew HorizontalLayoutManager();
            Root = recyclerView;
        }

        inline RecyclerView* getAdapterView() {
            return recyclerView;
        }

        __declspec(property(get = getAdapterView)) RecyclerView* RecyclerView;
    };

    class MenuBarWithBackgroundLayout:public MenuBarLayout {
    protected:
        SharedPointer<StackLayout> stack;
        SharedPointer<ColorView> backgroundView;

    public:
        MenuBarWithBackgroundLayout(ResourceContext& context, LayoutLoader& loader, Theme& theme):MenuBarLayout(context, loader, theme) {}

        virtual void init() override;

        inline ColorView* getBackgroundView() {
            return backgroundView;
        }

        __declspec(property(get = getBackgroundView)) ColorView* BackgroundView;
    };
}