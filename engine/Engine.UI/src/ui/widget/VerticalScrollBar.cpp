#include "ghuipch.h"
#include "VerticalScrollBar.h"

namespace Ghurund::UI {
    void VerticalScrollBar::updateBar() {
        if (maxScroll > 0) {
            Layout->BarButton->Visible = true;
            Layout->BarButton->PreferredSize.height = std::max(16.0f, Layout->Track->Size.height - MaxScroll);
            Layout->BarButton->setPosition(0, scroll / maxScroll * (Layout->Track->Size.height - Layout->BarButton->Size.height));
            Layout->TopButton->Enabled = true;
            Layout->BarButton->Enabled = true;
            Layout->BottomButton->Enabled = true;
        } else {
            Layout->BarButton->Visible = false;
            Layout->BarButton->setPosition(0, 0);
            Layout->TopButton->Enabled = false;
            Layout->BarButton->Enabled = false;
            Layout->BottomButton->Enabled = false;
        }
    }

    void VerticalScrollBar::updateScroll() {
        float trackLength = Layout->Track->Size.height - Layout->BarButton->Size.height;
        if (trackLength > 0) {
            scroll = Layout->BarButton->Position.y / trackLength * maxScroll;
            Layout->TopButton->Enabled = true;
            Layout->BarButton->Enabled = true;
            Layout->BottomButton->Enabled = true;
        } else {
            scroll = 0;
            Layout->TopButton->Enabled = false;
            Layout->BarButton->Enabled = false;
            Layout->BottomButton->Enabled = false;
        }
    }

    void VerticalScrollBar::onLayoutChanged() {
        __super::onLayoutChanged();
        if (dragHelper)
            delete dragHelper;
        dragHelper = ghnew DragHelper(*Layout->BarButton);

        Layout->TopButton->clicked += [this](Control&, const MouseClickedEventArgs&) {
            float prevScroll = scroll;
            Scroll -= 10;
            if (scroll != prevScroll) {
                Layout->Track->repaint();
                OnScrolled();
            }
            return true;
        };
        Layout->BottomButton->clicked += [this](Control&, const MouseClickedEventArgs&) {
            float prevScroll = scroll;
            Scroll += 10;
            if (scroll != prevScroll) {
                Layout->Track->repaint();
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
