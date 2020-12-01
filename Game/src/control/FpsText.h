#pragma once

#include "ui/control/TextBlock.h"
#include "core/collection/AverageValue.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class FpsText:public TextBlock {
    private:
        AverageValue<double> avgValue = AverageValue<double>(30, 20);

    public:
        FpsText(Ghurund::UI::Font* font, uint32_t color):TextBlock("", font, color) {}

        virtual void onUpdate(const Timer& timer) override {
            avgValue.set(1.0f / timer.FrameTime);
            Text = fmt::format("fps: {:.2f}", avgValue.get()).c_str();
            invalidate();
        }
    };
}