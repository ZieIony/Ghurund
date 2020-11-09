#pragma once

#include "ToolbarAdapter.h"

#include "core/ScopedPointer.h"
#include "ui/adapter/AdapterView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class Theme;

    class ToolbarLayout:public Layout {
    protected:
        Theme& theme;
        ScopedPointer<AdapterView<MenuItem*>> adapterView;

    public:
        ToolbarLayout(Theme& theme):theme(theme) {}

        virtual void init() override;

        inline AdapterView<MenuItem*>* getAdapterView() {
            return adapterView;
        }

        __declspec(property(get = getAdapterView)) AdapterView<MenuItem*>* AdapterView;
    };
}