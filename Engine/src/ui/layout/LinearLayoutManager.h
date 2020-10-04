#pragma once

#include "LayoutManager.h"
#include "ui/Gravity.h"
#include "ui/Orientation.h"

#include <algorithm>

namespace Ghurund::UI {
    class LinearLayoutManager:public LayoutManager {
    private:
        float contentSize = 0.0f;
        unsigned int spreadCount;

        FloatSize measureHorizontal(ControlGroup& group, float parentWidth, float parentHeight);

        FloatSize measureVertical(ControlGroup& group, float parentWidth, float parentHeight);

        void layoutHorizontal(ControlGroup& group, float x, float y, float width, float height);

        void layoutVertical(ControlGroup& group, float x, float y, float width, float height);

    public:
        Gravity gravity;
        Orientation orientation = Orientation::HORIZONTAL;

        virtual FloatSize measure(ControlGroup& group, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, float x, float y, float width, float height) override;
    };
}