#pragma once

#include "LayoutManager.h"

namespace Ghurund::UI {
    class VerticalLayoutManager:public LayoutManager {
    private:
        unsigned int indexTop = 0, indexBottom = 0;
        float firstTop = 0, firstBottom = 0;
        float lastTop = 0, lastBottom = 0;

        void addTop();
        void addBottom();
        void removeTop();
        void removeBottom();

    public:
        virtual void scrollBy(float dx, float dy) override;

        virtual const FloatSize measure(float parentWidth, float parentHeight) override;

        virtual void layout(float x, float y, float width, float height) override;
    };

}