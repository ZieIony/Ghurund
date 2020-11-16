#pragma once

#include "LayoutManager.h"

namespace Ghurund::UI {
    class HorizontalLayoutManager:public LayoutManager {
    private:
        unsigned int indexFirst = 0, indexLast = 0;
        float firstLeft = 0, firstRight = 0;
        float lastLeft = 0, lastRight = 0;

    public:
        virtual void scrollBy(ControlGroup& group, ChildrenProvider& provider, float dx, float dy) override {
            scroll.x += dx;
            if (dx > 0) {
                addLeft(group, provider, group.Size.width, group.Size.height);
                scroll.x = std::min(scroll.x, 0.0f);
                removeLeft(group, provider);
            } else {
                addRight(group, provider, group.Size.width, group.Size.height);
                if (indexFirst + group.Children.Size == provider.getChildCount())
                    scroll.y = std::max(scroll.y, -lastRight + group.Size.height);
                removeTop(group, provider);
            }
        }

        void addLeft(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) {
            while (firstLeft + scroll.x > 0 && indexFirst > 0) {
                indexFirst--;
                Control* control = provider.getChild(indexFirst);
                control->measure(parentWidth, parentHeight);
                control->layout(firstLeft - control->MeasuredSize.width, 0, control->MeasuredSize.width, group.Size.height);
                group.Children.insert(0, control);
                firstLeft = control->Position.x;
                firstRight = firstLeft + control->Size.width;
                control->release();
            }
        }

        void addRight(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) {
            while (lastRight + scroll.x < group.Size.width && provider.getChildCount()>indexLast) {
                Control* control = provider.getChild(indexLast);
                control->measure(parentWidth, parentHeight);
                control->layout(lastRight, 0, control->MeasuredSize.width, group.Size.height);
                group.Children.add(control);
                control->release();
                indexLast++;
                lastLeft = control->Position.x;
                lastRight = lastLeft + control->Size.width;
            }
        }

        void removeTop(ControlGroup& group, ChildrenProvider& provider) {
            while (group.Children.Size > 0 && firstRight + scroll.x < 0) {
                provider.releaseChild(group.Children[0], indexFirst);
                group.Children.removeAt(0);
                if (group.Children.Size > 0) {
                    Control* control = group.Children[0];
                    firstLeft = control->Position.x;
                    firstRight = firstLeft + control->Size.width;
                }
                indexFirst++;
            }
        }

        void removeLeft(ControlGroup& group, ChildrenProvider& provider) {
            while (group.Children.Size > 0 && lastLeft + scroll.x > group.Size.width) {
                indexLast--;
                provider.releaseChild(group.Children[group.Children.Size - 1], indexLast);
                group.Children.removeAt(group.Children.Size - 1);
                if (group.Children.Size > 0) {
                    Control* control = group.Children[group.Children.Size - 1];
                    lastLeft = control->Position.x;
                    lastRight = lastLeft + control->Size.width;
                }
            }
        }

        virtual const FloatSize measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) {
            if (group.PreferredSize.width == PreferredSize::Width::FILL &&
                group.PreferredSize.height == PreferredSize::Height::FILL)
                return { 0,0 };
            if ((float)group.PreferredSize.width >= 0 &&
                (float)group.PreferredSize.height >= 0) {
                return { (float)group.PreferredSize.width, (float)group.PreferredSize.height };
            }

            FloatSize measuredSize = { 0,0 };
            size_t i = indexFirst;
            while (i < provider.getChildCount()) {
                Control* control = provider.getChild(i);
                control->measure(parentWidth, parentHeight);
                if (control->PreferredSize.width != PreferredSize::Width::FILL)
                    measuredSize.width += control->MeasuredSize.width;
                if (control->PreferredSize.height != PreferredSize::Height::FILL)
                    measuredSize.height = std::max(measuredSize.height, control->MeasuredSize.height);
                provider.releaseChild(control, i);
                control->release();
                i++;
            }

            return measuredSize;
        }

        virtual void layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) {
            for (Control* c : group.Children) {
                if (c->Size.height != height)
                    c->layout(c->Position.x, 0, c->Size.width, height);
            }

            addLeft(group, provider, width, height);
            addRight(group, provider, width, height);

            if (indexFirst + group.Children.Size == provider.getChildCount())
                scroll.x = std::max(scroll.x, -lastRight + width);
            scroll.x = std::min(scroll.x, 0.0f);

            removeTop(group, provider);
            removeLeft(group, provider);
        }
    };

}