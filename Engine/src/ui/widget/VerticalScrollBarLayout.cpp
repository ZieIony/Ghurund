#include "VerticalScrollBarLayout.h"
#include "ui/Theme.h"
#include "ui/drawable/BitmapImageDrawable.h"

namespace Ghurund::UI {
    void VerticalScrollBarLayout::init() {
        auto topButtonLayout = ghnew ImageButtonFlatLayout();
        topButton = ghnew ImageButton(topButtonLayout);
        topButtonLayout->PaddingContainer->Padding.All = 0;
        topButton->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        topButton->Image = makeShared<BitmapImageDrawable>(theme.ArrowUp);

        barButton = ghnew ImageButton();
        barButton->PreferredSize = { PreferredSize::Width::FILL, 100.0f };

        clickableTrack = ghnew ClickableView();
        clickableTrack->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };

        track = ghnew ManualLayout();
        track->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        track->Children = { clickableTrack, barButton };

        auto bottomButtonLayout = ghnew ImageButtonFlatLayout();
        bottomButton = ghnew ImageButton(bottomButtonLayout);
        bottomButtonLayout->PaddingContainer->Padding.All = 0;
        bottomButton->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        bottomButton->Image = makeShared<BitmapImageDrawable>(theme.ArrowDown);

        verticalLayout = ghnew VerticalLayout();
        verticalLayout->Children = { topButton, track, bottomButton };
        verticalLayout->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::FILL };

        root = verticalLayout;
    }
}