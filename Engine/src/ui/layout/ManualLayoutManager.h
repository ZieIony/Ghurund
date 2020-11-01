#pragma once

#include "LayoutManager.h"

#include <algorithm>

namespace Ghurund::UI {
    class ManualLayoutManager:public LayoutManager {
    public:
        virtual FloatSize measure(ControlGroup& group, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, float x, float y, float width, float height) override;
    };
}