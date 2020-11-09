#pragma once

#include "MenuBarAdapter.h"

#include "core/ScopedPointer.h"
#include "ui/adapter/AdapterView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class MenuBarLayout:public Layout {
    protected:
        ScopedPointer<AdapterView<MenuItem*>> adapterView;
        Theme& theme;

    public:
        MenuBarLayout(Theme& theme):theme(theme) {}

        virtual void init() override {
            adapterView = ghnew Ghurund::UI::AdapterView<MenuItem*>();
            adapterView->PreferredSize.height = PreferredSize::Height::WRAP;
            adapterView->LayoutManager = ghnew HorizontalLayoutManager<MenuItem*, Control>();
            adapterView->Adapters.add(ghnew ButtonMenuBarAdapter(theme));
            root = adapterView;
        }

        inline AdapterView<MenuItem*>* getAdapterView() {
            return adapterView;
        }

        __declspec(property(get = getAdapterView)) AdapterView<MenuItem*>* AdapterView;
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