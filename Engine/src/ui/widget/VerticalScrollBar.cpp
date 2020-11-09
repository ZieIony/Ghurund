#include "VerticalScrollBar.h"
#include "ui/Theme.h"
#include "ui/drawable/BitmapImage.h"

namespace Ghurund::UI {
    void VerticalScrollBarLayout::init() {
        auto topButtonLayout = ghnew ImageButtonFlatLayout(theme);
        topButton = ghnew ImageButton(topButtonLayout);
        topButtonLayout->PaddingContainer->Padding.All = 0;
        topButton->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);
        ScopedPointer<BitmapImage> arrowUpImage = ghnew BitmapImage("icons/arrow up 18.png");
        topButton->Image = arrowUpImage;

        barButton = ghnew ImageButton(theme);
        barButton->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height(100));

        clickableTrack = ghnew ClickableView();
        clickableTrack->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::FILL);

        track = ghnew ManualLayout();
        track->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::FILL);
        track->Children = { clickableTrack, barButton };

        auto bottomButtonLayout = ghnew ImageButtonFlatLayout(theme);
        bottomButton = ghnew ImageButton(bottomButtonLayout);
        bottomButtonLayout->PaddingContainer->Padding.All = 0;
        bottomButton->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);
        ScopedPointer<BitmapImage> arrowDownImage = ghnew BitmapImage("icons/arrow down 18.png");
        bottomButton->Image = arrowDownImage;

        verticalLayout = ghnew VerticalLayout();
        verticalLayout->Children = { topButton, track, bottomButton };
        verticalLayout->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::FILL);

        root = verticalLayout;
    }

    void VerticalScrollBar::updateBar() {
        if (maxScroll > 0) {
            Layout.BarButton->setPosition(0, scroll / maxScroll * (Layout.Track->Size.height - Layout.BarButton->Size.height));
            Layout.TopButton->Enabled = true;
            Layout.BarButton->Enabled = true;
            Layout.BottomButton->Enabled = true;
        } else {
            Layout.BarButton->setPosition(0, 0);
            Layout.TopButton->Enabled = false;
            Layout.BarButton->Enabled = false;
            Layout.BottomButton->Enabled = false;
        }
    }

    void VerticalScrollBar::updateScroll() {
        float trackLength = Layout.Track->Size.height - Layout.BarButton->Size.height;
        if (trackLength > 0) {
            scroll = Layout.BarButton->Position.y / trackLength * maxScroll;
            Layout.TopButton->Enabled = true;
            Layout.BarButton->Enabled = true;
            Layout.BottomButton->Enabled = true;
        } else {
            scroll = 0;
            Layout.TopButton->Enabled = false;
            Layout.BarButton->Enabled = false;
            Layout.BottomButton->Enabled = false;
        }
    }

    VerticalScrollBar::VerticalScrollBar(VerticalScrollBarLayout* layout):Widget(layout) {
        setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::FILL);

        layout->TopButton->OnClicked.add([this, layout](Control&, const MouseClickedEventArgs&) {
            float prevScroll = scroll;
            Scroll -= 10;
            if (scroll != prevScroll) {
                layout->Track->repaint();
                OnScrolled();
            }
            return true;
        });
        layout->BottomButton->OnClicked.add([this, layout](Control&, const MouseClickedEventArgs&) {
            float prevScroll = scroll;
            Scroll += 10;
            if (scroll != prevScroll) {
                layout->Track->repaint();
                OnScrolled();
            }
            return true;
        });
        layout->BarButton->OnMouseButton.add([this, layout](EventConsumer& sender, const MouseButtonEventArgs& args) {
            if (args.Action == MouseAction::DOWN && args.Button == MouseButton::LEFT) {
                pressBarPos = layout->BarButton->Position.y;
                pressMousePos = pressBarPos + args.Position.y;
            }
            return true;
        });
        layout->BarButton->OnMouseMotion.add([this, layout](EventConsumer& sender, const MouseMotionEventArgs& args) {
            if (layout->BarButton->Pressed[MouseButton::LEFT]) {
                float prevScroll = scroll;
                float maxPos = layout->Track->Size.height - layout->BarButton->Size.height;
                float mousePos = layout->BarButton->Position.y + args.Position.y;
                float y = std::max(0.0f, std::min((float)(pressBarPos + mousePos - pressMousePos), maxPos));
                layout->BarButton->setPosition(0, y);
                updateScroll();
                if (scroll != prevScroll) {
                    layout->Track->repaint();
                    OnScrolled();
                }
            }
            return false;
        });
    }
}
