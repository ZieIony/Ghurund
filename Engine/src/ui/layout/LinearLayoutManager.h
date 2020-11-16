#pragma once

#include "LayoutManager.h"
#include "ui/Alignment.h"
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
        Alignment alignment;
        Orientation orientation = Orientation::HORIZONTAL;

        virtual const FloatSize measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) override;
    };
}