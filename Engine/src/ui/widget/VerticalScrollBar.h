#pragma once

#include "Widget.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/ManualLayout.h"
#include "ui/widget/button/ImageButton.h"

#include <algorithm>

namespace Ghurund::UI {
    class VerticalScrollBarLayout:public Layout {
    private:
        Theme& theme;
        ScopedPointer<ImageButton> topButton;
        ScopedPointer<Button> barButton;
        ScopedPointer<ClickableView> clickableTrack;
        ManualLayoutPtr track;
        ScopedPointer<ImageButton> bottomButton;
        VerticalLayoutPtr verticalLayout;
        ImagePtr arrowUp, arrowDown;

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

    class VerticalScrollBar:public Widget2<VerticalScrollBarLayout> {
    private:
        uint32_t pressMousePos = 0;
        float pressBarPos = 0;

        float scroll = 0;
        float maxScroll = 100;
        Event<Control> onScrolled = Event<Control>(*this);

        void updateBar();

        void updateScroll();

    public:
        VerticalScrollBar(VerticalScrollBarLayout* layout);

        VerticalScrollBar(Theme& theme):VerticalScrollBar(ghnew VerticalScrollBarLayout(theme)) {}

        inline float getScroll() const {
            return scroll;
        }

        inline void setScroll(float scroll) {
            this->scroll = std::max(0.0f, std::min(scroll, maxScroll));
            updateBar();
        }

        __declspec(property(get = getScroll, put = setScroll)) float Scroll;

        inline float getMaxScroll() const {
            return maxScroll;
        }

        inline void setMaxScroll(float maxScroll) {
            this->maxScroll = std::max(0.0f, maxScroll);
            Scroll = std::max(0.0f, std::min(scroll, maxScroll));
        }

        __declspec(property(get = getMaxScroll, put = setMaxScroll)) float MaxScroll;

        inline Event<Control>& getOnScrolled() {
            return onScrolled;
        }

        __declspec(property(get = getOnScrolled)) Event<Control>& OnScrolled;
    };

    typedef ScopedPointer<VerticalScrollBar> VerticalScrollBarPtr;
}