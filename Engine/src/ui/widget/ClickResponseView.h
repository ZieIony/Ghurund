#pragma once

#include "ui/control/ClickableView.h"

#include <ctime>

namespace Ghurund::UI {
    class ClickResponseView:public ClickableView {
    private:
        uint64_t startTime = 0;
        uint32_t length = 150;
        Paint paint;
        bool finishedAnimating = true;

    public:
        uint32_t color = 0x3f0078D7;

        ClickResponseView() {
            OnClicked.add([this](Control&, const MouseClickedEventArgs& event) {
                startTime = event.TimeMs;
                return true;
            });
        }

        virtual void update(const Timer& timer) override;

        virtual void onDraw(Canvas& canvas) override {
            __super::onDraw(canvas);
            canvas.fillRect(0, 0, Size.width, Size.height, paint);
            if (!finishedAnimating)
                repaint();
        }
    };
}