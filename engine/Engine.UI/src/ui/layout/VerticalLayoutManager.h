#pragma once

#include "LayoutManager.h"

namespace Ghurund::UI {
    class VerticalLayoutManager:public LayoutManager {
    private:
        unsigned int indexTop = 0, indexBottom = 0;
        float firstTop = 0, firstBottom = 0;
        float lastTop = 0, lastBottom = 0;

        void addTop(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight);

        void addBottom(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight);

        void removeTop(ControlGroup& group, ChildrenProvider& provider);

        void removeBottom(ControlGroup& group, ChildrenProvider& provider);

    public:
        virtual void scrollBy(ControlGroup& group, ChildrenProvider& provider, float dx, float dy) override;

        virtual const FloatSize measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) override;
    };

}