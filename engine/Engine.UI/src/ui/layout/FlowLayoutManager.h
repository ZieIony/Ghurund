#pragma once

#include "LayoutManager.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    struct Spacing {
        float horizontal = 0.0f, vertical = 0.0f;
    };

    class FlowLayoutManager:public LayoutManager {
    private:
        void layoutFlowingControlsRight(float width);

        void layoutFlowingControlsLeft(float width);

        float measureWidth();

        float measureHeight(float width);

    public:
        bool reverseLayout = false;
        Spacing spacing;

        virtual const FloatSize measure() override;

        virtual void layout(float x, float y, float width, float height) override;
    };
}