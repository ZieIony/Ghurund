#include "VerticalScrollBar.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void VerticalScrollBarLayout::init() {
        arrowUp = ghnew GdiImage("icons/arrow up 18.png");
        arrowDown = ghnew GdiImage("icons/arrow down 18.png");

        topButton = ghnew ImageButton(theme);
        topButton->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);
        topButton->Image = arrowUp;

        barButton = ghnew ImageButton(theme);
        barButton->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height(100));

        StackLayoutPtr track = ghnew StackLayout();
        track->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::FILL);
        track->Children = { barButton };

        bottomButton = ghnew ImageButton(theme);
        bottomButton->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);
        bottomButton->Image = arrowDown;

        verticalLayout = ghnew VerticalLayout();
        verticalLayout->Children = { topButton, track, bottomButton };
        verticalLayout->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::FILL);

        root = verticalLayout;
    }
}
