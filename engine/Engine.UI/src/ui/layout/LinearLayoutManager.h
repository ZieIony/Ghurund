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

        Ghurund::Core::FloatSize measureHorizontal(float parentWidth, float parentHeight);

        Ghurund::Core::FloatSize measureVertical(float parentWidth, float parentHeight);

        void layoutHorizontal(float x, float y, float width, float height);

        void layoutVertical(float x, float y, float width, float height);

    public:
        Alignment alignment;
        Orientation orientation = Orientation::HORIZONTAL;

        virtual const Ghurund::Core::FloatSize measure(float parentWidth, float parentHeight) override;

        virtual void layout(float x, float y, float width, float height) override;
    };
}