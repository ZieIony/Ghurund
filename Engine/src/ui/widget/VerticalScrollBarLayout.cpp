#include "VerticalScrollBarLayout.h"
#include "ui/LayoutLoader.h"
#include "ui/drawable/BitmapImageDrawable.h"

namespace Ghurund::UI {
    VerticalScrollBarLayout::VerticalScrollBarLayout(LayoutLoader& loader) {
        PointerList<Control*> controls;
        if (loader.load(FilePath(L"layouts/VerticalScrollBar.xml"), controls) == Status::OK)
            Root = controls[0];
    }

    void VerticalScrollBarLayout::init() {
        topButton = (Button*)Root->find("startButton");
        barButton = (Button*)Root->find("barButton");
        clickableTrack = (ClickableControl*)Root->find("clickableTrack");
        track = (ManualLayout*)Root->find("track");
        bottomButton = (Button*)Root->find("endButton");
    }
}
