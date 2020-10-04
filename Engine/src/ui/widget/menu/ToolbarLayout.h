#pragma once

#include "ToolbarAdapter.h"
#include "core/ScopedPointer.h"
#include "ui/widget/Widget.h"
#include "ui/control/ColorView.h"
#include "ui/control/StackLayout.h"
#include "ui/control/AdapterView.h"
#include "ui/layout/HorizontalLayoutManager.h"

namespace Ghurund::UI {
    class ToolbarLayout:public Layout {
    protected:
        ScopedPointer<AdapterView<MenuItem*>> adapterView;

    public:
        ToolbarLayout() {
            adapterView = ghnew Ghurund::UI::AdapterView<MenuItem*>();
            root = adapterView;
        }

        inline AdapterView<MenuItem*>* getAdapterView() {
            return adapterView;
        }

        __declspec(property(get = getAdapterView)) AdapterView<MenuItem*>* AdapterView;
    };

    class ToolbarWithBackgroundLayout:public ToolbarLayout {
    protected:
        ScopedPointer<StackLayout> stack;
        ScopedPointer<ColorView> backgroundView;

    public:
        ToolbarWithBackgroundLayout() {
            stack = ghnew StackLayout();
            backgroundView = ghnew ColorView();
            stack->Children = { backgroundView, adapterView };
            root = stack;
        }

        inline ColorView* getBackgroundView() {
            return backgroundView;
        }

        __declspec(property(get = getBackgroundView)) ColorView* BackgroundView;
    };
}