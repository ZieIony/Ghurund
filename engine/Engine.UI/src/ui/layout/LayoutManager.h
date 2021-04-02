#pragma once

#include "ui/control/ChildrenProvider.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class LayoutManager {
    protected:
        FloatPoint scroll = { 0,0 };
        FloatPoint maxScroll = { 0.0f, 0.0f };

        float measureMaxWidth(ControlGroup& group);

        float measureMaxHeight(ControlGroup& group);

    public:
        virtual ~LayoutManager() = 0 {}

        inline const FloatPoint& getScroll() const {
            return scroll;
        }

        inline void setScroll(const FloatPoint& scroll) {
            this->scroll = scroll;
        }

        __declspec(property(get = getScroll, put = setScroll)) const FloatPoint& Scroll;

        virtual void scrollBy(ControlGroup& group, ChildrenProvider& provider, float dx, float dy) {}

        inline const FloatPoint& getMaxScroll() const {
            return maxScroll;
        }

        __declspec(property(get = getMaxScroll)) const FloatPoint& MaxScroll;

        virtual const FloatSize measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) {
            for (Control* c : group.Children) {
                c->measure(
                    group.PreferredSize.width >= 0 ? (float)group.PreferredSize.width : parentWidth,
                    group.PreferredSize.height >= 0 ? (float)group.PreferredSize.height : parentHeight
                );
            }
            return { 0,0 };
        }

        virtual void layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) = 0;
    };
}