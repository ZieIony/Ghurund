#pragma once

#include "LayoutBinding.h"
#include "ui/widget/Widget.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/layout/StackLayout.h"
#include <TestRecycler.h>

namespace Demo {
    using namespace Ghurund::UI;

    class DemoLayout:public Widget<LayoutBinding> {
    private:
        TestRecycler* testRecycler;

    protected:
        virtual void onLayoutChanged() override {
            if (!Layout)
                return;

            testRecycler = ghnew TestRecycler();
            Layout->Container->Children.add(testRecycler);
        }

    public:
        inline StackLayout* getContainer() {
            return Layout->Container;
        }

        __declspec(property(get = getContainer)) StackLayout* Container;
    };
}