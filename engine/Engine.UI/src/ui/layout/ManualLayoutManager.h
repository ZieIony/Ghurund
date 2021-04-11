#pragma once

#include "LayoutManager.h"

#include <algorithm>

namespace Ghurund::UI {
    class ManualLayoutManager:public LayoutManager {
    public:
        virtual const FloatSize measure(float parentWidth, float parentHeight) override;

        virtual void layout(float x, float y, float width, float height) override;
    };
}