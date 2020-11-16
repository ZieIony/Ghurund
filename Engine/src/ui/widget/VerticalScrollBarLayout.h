#pragma once

#include "ui/layout/LinearLayout.h"
#include "ui/layout/ManualLayout.h"
#include "ui/widget/button/ImageButton.h"

namespace Ghurund::UI {
    class VerticalScrollBarLayout:public WidgetLayout {
    private:
        Theme& theme;
        ScopedPointer<ImageButton> topButton;
        ScopedPointer<Button> barButton;
        ScopedPointer<ClickableView> clickableTrack;
        ManualLayoutPtr track;
        ScopedPointer<ImageButton> bottomButton;
        ScopedPointer<VerticalLayout> verticalLayout;

    public:
        VerticalScrollBarLayout(Theme& theme):theme(theme) {}

        virtual void init() override;

        inline ImageButton* getTopButton() {
            return topButton;
        }

        __declspec(property(get = getTopButton)) ImageButton* TopButton;

        inline Button* getBarButton() {
            return barButton;
        }

        __declspec(property(get = getBarButton)) Button* BarButton;

        inline ClickableView* getClickableTrack() {
            return clickableTrack;
        }

        __declspec(property(get = getClickableTrack)) ClickableView* ClickableTrack;

        inline Control* getTrack() {
            return track;
        }

        __declspec(property(get = getTrack)) Control* Track;

        inline ImageButton* getBottomButton() {
            return bottomButton;
        }

        __declspec(property(get = getBottomButton)) ImageButton* BottomButton;
    };
}