#include "ghuipch.h"
#include "VerticalScrollBar.h"

namespace Ghurund::UI {
    void VerticalScrollBar::updateBar() {
        if (maxScroll > 0) {
            barButton->Visible = true;
            barButton->PreferredSize.height = std::max(16.0f, track->Size.height - MaxScroll);
            barButton->setPosition(0, scroll / maxScroll * (track->Size.height - barButton->Size.height));
            topButton->Enabled = true;
            barButton->Enabled = true;
            bottomButton->Enabled = true;
        } else {
            barButton->Visible = false;
            barButton->setPosition(0, 0);
            topButton->Enabled = false;
            barButton->Enabled = false;
            bottomButton->Enabled = false;
        }
    }

    void VerticalScrollBar::updateScroll() {
        float trackLength = track->Size.height - barButton->Size.height;
        if (trackLength > 0) {
            scroll = barButton->Position.y / trackLength * maxScroll;
            topButton->Enabled = true;
            barButton->Enabled = true;
            bottomButton->Enabled = true;
        } else {
            scroll = 0;
            topButton->Enabled = false;
            barButton->Enabled = false;
            bottomButton->Enabled = false;
        }
    }

    void VerticalScrollBar::bind() {
        __super::bind();
        topButton = (Button*)find("startButton");
        barButton = (Button*)find("barButton");
        clickableTrack = (ClickableControl*)find("clickableTrack");
        track = (ManualLayout*)find("track");
        bottomButton = (Button*)find("endButton");
        if (dragHelper)
            delete dragHelper;
        dragHelper = ghnew DragHelper(*barButton);

        topButton->clicked += [this](Control&, const MouseClickedEventArgs&) {
            float prevScroll = scroll;
            Scroll -= 10;
            if (scroll != prevScroll) {
                track->repaint();
                OnScrolled();
            }
            return true;
        };
        bottomButton->clicked += [this](Control&, const MouseClickedEventArgs&) {
            float prevScroll = scroll;
            Scroll += 10;
            if (scroll != prevScroll) {
                track->repaint();
                OnScrolled();
            }
            return true;
        };
        dragHelper->dragged += [this](Control& control) {
            updateScroll();
            OnScrolled();
            return true;
        };
    }
}
