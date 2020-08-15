#pragma once

#include "ui/control/Button.h"
#include "ui/control/Column.h"

namespace Ghurund::UI {
    class VerticalScrollBar:public Column {
    private:
        Button* topButton;
        Button* barButton;
        Button* bottomButton;

    public:
        VerticalScrollBar() {
            topButton = ghnew Button();
            topButton->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::WRAP);
            barButton = ghnew Button();
            barButton->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height(100));
            bottomButton = ghnew Button();
            bottomButton->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::WRAP);

            Children.add({ topButton, barButton, bottomButton });
        }
    };
}