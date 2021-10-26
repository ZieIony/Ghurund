#include "ghuipch.h"
#include "VerticalLayoutManager.h"

namespace Ghurund::UI {
    void VerticalLayoutManager::addTop() {
        while (firstTop + scroll.y > 0 && indexTop > 0) {
            indexTop--;
            Control* control = provider->getChild(indexTop);
            control->measure(group->Size.width, group->Size.height);
            control->layout(0, firstTop - control->MeasuredSize.height, group->Size.width, control->MeasuredSize.height);
            group->Children.insert(0, control);
            firstTop = control->Position.y;
            firstBottom = firstTop + control->Size.height;
            control->release();
        }
    }

    void VerticalLayoutManager::addBottom() {
        while (lastBottom + scroll.y < group->Size.height && provider->getChildCount()>indexBottom) {
            Control* control = provider->getChild(indexBottom);
            control->measure(group->Size.width, group->Size.height);
            control->layout(0, lastBottom, group->Size.width, control->MeasuredSize.height);
            group->Children.add(control);
            control->release();
            indexBottom++;
            lastTop = control->Position.y;
            lastBottom = lastTop + control->Size.height;
        }
    }

    void VerticalLayoutManager::removeTop() {
        while (group->Children.Size > 0 && firstBottom + scroll.y < 0) {
            provider->releaseChild(group->Children[0], indexTop);
            group->Children.removeAt(0);
            if (group->Children.Size > 0) {
                Control* control = group->Children[0];
                firstTop = control->Position.y;
                firstBottom = firstTop + control->Size.height;
            }
            indexTop++;
        }
    }

    void VerticalLayoutManager::removeBottom() {
        while (group->Children.Size > 0 && lastTop + scroll.y > group->Size.height) {
            indexBottom--;
            provider->releaseChild(group->Children[group->Children.Size - 1], indexBottom);
            group->Children.removeAt(group->Children.Size - 1);
            if (group->Children.Size > 0) {
                Control* control = group->Children[group->Children.Size - 1];
                lastTop = control->Position.y;
                lastBottom = lastTop + control->Size.height;
            }
        }
    }

    void VerticalLayoutManager::scrollBy(float dx, float dy) {
        scroll.y += dy;
        if (dy > 0) {
            addTop();
            scroll.y = std::min(scroll.y, 0.0f);
            removeBottom();
        } else {
            addBottom();
            if (indexTop + group->Children.Size == provider->getChildCount())
                scroll.y = std::max(scroll.y, -lastBottom + group->Size.height);
            removeTop();
        }
    }

    const FloatSize VerticalLayoutManager::measure(float parentWidth, float parentHeight) {
        if (group->PreferredSize.width == PreferredSize::Width::FILL && group->PreferredSize.height == PreferredSize::Height::FILL)
            return { 0, 0 };
        if (group->PreferredSize.width.Type == PreferredSize::Type::PIXELS && group->PreferredSize.height.Type == PreferredSize::Type::PIXELS)
            return { group->PreferredSize.width.Value, group->PreferredSize.height.Value };

        float width = 0;
        float height = 0;
        for (size_t i = 0; i < provider->getChildCount(); i++) {
            Control* control = provider->getChild(i);
            control->measure(parentWidth, parentHeight);
            if (control->PreferredSize.width != PreferredSize::Width::FILL)
                width = std::max(width, control->MeasuredSize.width);
            if (control->PreferredSize.height != PreferredSize::Height::FILL)
                height += control->MeasuredSize.height;
            maxScroll.y += control->MeasuredSize.height;
            provider->releaseChild(control, i);
        }

        if (group->PreferredSize.width.Type == PreferredSize::Type::PIXELS)
            width = group->PreferredSize.width.Value;
        if (group->PreferredSize.height.Type == PreferredSize::Type::PIXELS)
            height = group->PreferredSize.height.Value;
        return { width, height };
    }

    void VerticalLayoutManager::layout(float x, float y, float width, float height) {
        for (Control* c : group->Children) {
            if (c->Size.width != width)
                c->layout(0, c->Position.y, width, c->Size.height);
        }

        addTop();
        addBottom();

        if (indexTop + group->Children.Size == provider->getChildCount())
            scroll.y = std::max(scroll.y, -lastBottom + height);
        scroll.y = std::min(scroll.y, 0.0f);

        removeTop();
        removeBottom();
    }
}
