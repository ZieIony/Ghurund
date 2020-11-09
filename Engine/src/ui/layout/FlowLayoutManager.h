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

        int measureHeight(ControlGroup& group, int width);

    public:
        bool reverseLayout = false;
        Spacing spacing;

        virtual FloatSize measure(ControlGroup& group, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, float x, float y, float width, float height) override;
    };
}