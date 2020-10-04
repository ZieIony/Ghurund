#pragma once

#include "LayoutManager.h"
#include "ui/Gravity.h"

#include <algorithm>

namespace Ghurund::UI {
    class StackLayoutManager:public LayoutManager {
    public:
        Gravity gravity;

        virtual FloatSize measure(ControlGroup& group, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, float x, float y, float width, float height) override;
    };
}