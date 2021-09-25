#pragma once

#include "LayoutManager.h"
#include "ui/Alignment.h"

#include <algorithm>

namespace Ghurund::UI {
    class StackLayoutManager:public LayoutManager {
    public:
        Alignment alignment;

        virtual const Ghurund::Core::FloatSize measure(float parentWidth, float parentHeight) override;

        virtual void layout(float x, float y, float width, float height) override;
    };
}