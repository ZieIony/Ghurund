#pragma once

#include "ui/layout/LinearLayout.h"
#include "ui/layout/ManualLayout.h"
#include "ui/widget/button/Button.h"

namespace Ghurund::UI {
    class LayoutLoader;

    class VerticalScrollBarLayout:public WidgetLayout {
    private:
        Button* topButton;
        Button* barButton;
        ClickableControl* clickableTrack;
        ManualLayout* track;
        Button* bottomButton;

    public:
        VerticalScrollBarLayout(LayoutLoader& loader);

        VerticalScrollBarLayout(Control* layout) {
            Root = layout;
        }

        virtual void init() override;

        inline Button* getTopButton() {
            return topButton;
        }

        __declspec(property(get = getTopButton)) Button* TopButton;

        inline Button* getBarButton() {
            return barButton;
        }

        __declspec(property(get = getBarButton)) Button* BarButton;

        inline ClickableControl* getClickableTrack() {
            return clickableTrack;
        }

        __declspec(property(get = getClickableTrack)) ClickableControl* ClickableTrack;

        inline Control* getTrack() {
            return track;
        }

        __declspec(property(get = getTrack)) Control* Track;

        inline Button* getBottomButton() {
            return bottomButton;
        }

        __declspec(property(get = getBottomButton)) Button* BottomButton;
    };
}