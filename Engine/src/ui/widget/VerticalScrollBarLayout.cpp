#include "VerticalScrollBarLayout.h"
#include "ui/Theme.h"
#include "ui/drawable/BitmapImage.h"

namespace Ghurund::UI {
    void VerticalScrollBarLayout::init() {
        auto topButtonLayout = ghnew ImageButtonFlatLayout(theme);
        topButton = ghnew ImageButton(topButtonLayout);
        topButtonLayout->PaddingContainer->Padding.All = 0;
        topButton->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        topButton->Image = theme.ArrowUp;

        barButton = ghnew ImageButton(theme);
        barButton->PreferredSize = { PreferredSize::Width::FILL, 100.0f };

        clickableTrack = ghnew ClickableView();
        clickableTrack->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };

        track = ghnew ManualLayout();
        track->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        track->Children = { clickableTrack, barButton };

        auto bottomButtonLayout = ghnew ImageButtonFlatLayout(theme);
        bottomButton = ghnew ImageButton(bottomButtonLayout);
        bottomButtonLayout->PaddingContainer->Padding.All = 0;
        bottomButton->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        bottomButton->Image = theme.ArrowDown;

        verticalLayout = ghnew VerticalLayout();
        verticalLayout->Children = { topButton, track, bottomButton };
        verticalLayout->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::FILL };

        root = verticalLayout;
    }
}
