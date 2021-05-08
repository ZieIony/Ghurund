#pragma once

#include "core/collection/AverageValue.h"
#include "ui/text/TextBlock.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class FpsText:public TextBlock {
    private:
        AverageValue<double> avgValue = AverageValue<double>(30, 20);
        const Timer& timer;

    public:
        FpsText(Ghurund::UI::TextFormat* textFormat, uint32_t color, const Timer& timer):TextBlock(L"", color, textFormat), timer(timer) {}

        virtual void onUpdate(const uint64_t time) override {
            avgValue.set(1.0f / timer.FrameTime);
            Text = fmt::format(L"fps: {:.2f}", avgValue.get()).c_str();
            invalidate();
        }
    };
}