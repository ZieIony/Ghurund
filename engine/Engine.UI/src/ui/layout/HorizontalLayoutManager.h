#pragma once

#include "LayoutManager.h"

namespace Ghurund::UI {
    class HorizontalLayoutManager:public LayoutManager {
    private:
        unsigned int indexFirst = 0, indexLast = 0;
        float firstLeft = 0, firstRight = 0;
        float lastLeft = 0, lastRight = 0;

    public:
        virtual void scrollBy(float dx, float dy) override {
            scroll.x += dx;
            if (dx > 0) {
                addLeft(group->Size.Width, group->Size.Height);
                scroll.x = std::min(scroll.x, 0.0f);
                removeLeft();
            } else {
                addRight(group->Size.Width, group->Size.Height);
                if (indexFirst + group->Children.Size == provider->getChildCount())
                    scroll.y = std::max(scroll.y, -lastRight + group->Size.Height);
                removeTop();
            }
        }

        void addLeft(float parentWidth, float parentHeight) {
            while (firstLeft + scroll.x > 0 && indexFirst > 0) {
                indexFirst--;
                Control* control = provider->getChild(indexFirst);
                //control->measure(parentWidth, parentHeight);
                control->layout(firstLeft - control->MeasuredSize.Width, 0, control->MeasuredSize.Width, group->Size.Height);
                group->Children.insert(0, control);
                firstLeft = control->Position.x;
                firstRight = firstLeft + control->Size.Width;
                control->release();
            }
        }

        void addRight(float parentWidth, float parentHeight) {
            while (lastRight + scroll.x < group->Size.Width && provider->getChildCount()>indexLast) {
                Control* control = provider->getChild(indexLast);
                //control->measure(parentWidth, parentHeight);
                control->layout(lastRight, 0, control->MeasuredSize.Width, group->Size.Height);
                group->Children.add(control);
                control->release();
                indexLast++;
                lastLeft = control->Position.x;
                lastRight = lastLeft + control->Size.Width;
            }
        }

        void removeTop() {
            while (group->Children.Size > 0 && firstRight + scroll.x < 0) {
                provider->releaseChild(group->Children[0], indexFirst);
                group->Children.removeAt(0);
                if (group->Children.Size > 0) {
                    Control* control = group->Children[0];
                    firstLeft = control->Position.x;
                    firstRight = firstLeft + control->Size.Width;
                }
                indexFirst++;
            }
        }

        void removeLeft() {
            while (group->Children.Size > 0 && lastLeft + scroll.x > group->Size.Width) {
                indexLast--;
                provider->releaseChild(group->Children[group->Children.Size - 1], indexLast);
                group->Children.removeAt(group->Children.Size - 1);
                if (group->Children.Size > 0) {
                    Control* control = group->Children[group->Children.Size - 1];
                    lastLeft = control->Position.x;
                    lastRight = lastLeft + control->Size.Width;
                }
            }
        }

        virtual const Ghurund::Core::FloatSize measure() {
            Ghurund::Core::FloatSize measuredSize = { 0,0 };
            return measuredSize;
        }

        virtual void layout(float x, float y, float width, float height) {
            for (Control* c : group->Children) {
                if (c->Size.Height != height)
                    c->layout(c->Position.x, 0, c->Size.Width, height);
            }

            addLeft(width, height);
            addRight(width, height);

            if (indexFirst + group->Children.Size == provider->getChildCount())
                scroll.x = std::max(scroll.x, -lastRight + width);
            scroll.x = std::min(scroll.x, 0.0f);

            removeTop();
            removeLeft();
        }
    };

}