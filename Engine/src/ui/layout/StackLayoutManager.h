#pragma once

#include "LayoutManager.h"
#include "ui/Alignment.h"

#include <algorithm>

namespace Ghurund::UI {
    class StackLayoutManager:public LayoutManager {
    public:
        Alignment alignment;

        virtual const FloatSize measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) override;
    };
}