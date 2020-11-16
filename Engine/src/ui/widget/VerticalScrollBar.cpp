#include "VerticalScrollBar.h"

namespace Ghurund::UI {
    void VerticalScrollBar::updateBar() {
        if (maxScroll > 0) {
            Layout.BarButton->Visible = true;
            Layout.BarButton->PreferredSize.height = std::max(16.0f, Layout.Track->Size.height - MaxScroll);
            Layout.BarButton->setPosition(0, scroll / maxScroll * (Layout.Track->Size.height - Layout.BarButton->Size.height));
            Layout.TopButton->Enabled = true;
            Layout.BarButton->Enabled = true;
            Layout.BottomButton->Enabled = true;
        } else {
            Layout.BarButton->Visible = false;
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

    VerticalScrollBar::VerticalScrollBar(VerticalScrollBarLayout* layout):Widget(layout), dragHelper(DragHelper(*layout->BarButton)) {
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
        dragHelper.OnDragged.add([this](Control& control) {
            updateScroll();
            OnScrolled();
            return true;
        });
    }
}
