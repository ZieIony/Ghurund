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

        Ghurund::Core::FloatSize measureHorizontal();

        Ghurund::Core::FloatSize measureVertical();

        void layoutHorizontal(float x, float y, float width, float height);

        void layoutVertical(float x, float y, float width, float height);

    public:
        Alignment alignment;
        Orientation orientation = Orientation::HORIZONTAL;

        virtual const Ghurund::Core::FloatSize measure() override;

        virtual void layout(float x, float y, float width, float height) override;
    };
}