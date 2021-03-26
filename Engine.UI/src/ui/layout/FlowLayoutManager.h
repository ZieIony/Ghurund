#pragma once

#include "LayoutManager.h"

namespace Ghurund::UI {
    struct Spacing {
        float horizontal = 0.0f, vertical = 0.0f;
    };

    class FlowLayoutManager:public LayoutManager {
    private:
        void layoutFlowingControlsRight(ControlGroup& group, float width);

        void layoutFlowingControlsLeft(ControlGroup& group, float width);

        float measureWidth(ControlGroup& group);

        float measureHeight(ControlGroup& group, float width);

    public:
        bool reverseLayout = false;
        Spacing spacing;

        virtual const FloatSize measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) override;
    };
}