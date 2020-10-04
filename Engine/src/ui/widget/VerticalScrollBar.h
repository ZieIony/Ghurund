#pragma once

#include "Widget.h"
#include "ui/control/LinearLayout.h"
#include "ui/widget/button/ImageButton.h"

namespace Ghurund::UI {
    class VerticalScrollBarLayout:public Layout {
    private:
        Theme& theme;
        ImageButton* topButton = nullptr;
        Button* barButton = nullptr;
        ImageButton* bottomButton = nullptr;
        VerticalLayout* verticalLayout = nullptr;
        GdiImage* arrowUp = nullptr;
        GdiImage* arrowDown = nullptr;

    public:
        VerticalScrollBarLayout(Theme& theme):theme(theme) {}

        virtual void init() override;

        ~VerticalScrollBarLayout() {
            if (topButton)
                topButton->release();
            if (barButton)
                barButton->release();
            if (bottomButton)
                bottomButton->release();
            if (verticalLayout)
                verticalLayout->release();
        }
    };

    class VerticalScrollBar:public Widget2<VerticalScrollBarLayout> {
    public:
        VerticalScrollBar(VerticalScrollBarLayout* layout):Widget2(layout) {
            setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::FILL);
        }
    };
}