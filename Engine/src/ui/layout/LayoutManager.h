#pragma once

#include "ui/control/ChildrenProvider.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class LayoutManager {
    protected:
        XMFLOAT2 scroll = { 0,0 };
        XMFLOAT2 maxScroll = { 0.0f, 0.0f };

        inline float measureMaxWidth(ControlGroup& group) {
            float measuredWidth = 0;
            if (group.PreferredSize.width >= 0) {
                measuredWidth = (float)group.PreferredSize.width;
            } else {
                for (Control* c : group.Children) {
                    if (c->PreferredSize.width >= 0) {
                        measuredWidth = std::max(measuredWidth, (float)c->PreferredSize.width);
                        measuredWidth = std::max(measuredWidth, c->MinSize.width);
                    } else {
                        measuredWidth = std::max(measuredWidth, c->MeasuredSize.width);
                    }
                }
            }
            return std::max(group.MinSize.width, measuredWidth);
        }

        inline float measureMaxHeight(ControlGroup& group) {
            float measuredHeight = 0;
            if (group.PreferredSize.height >= 0) {
                measuredHeight = (float)group.PreferredSize.height;
            } else {
                for (Control* c : group.Children) {
                    if (c->PreferredSize.width >= 0) {
                        measuredHeight = std::max(measuredHeight, (float)c->PreferredSize.height);
                        measuredHeight = std::max(measuredHeight, c->MinSize.height);
                    } else {
                        measuredHeight = std::max(measuredHeight, c->MeasuredSize.height);
                    }
                }
            }
            return std::max(group.MinSize.height, measuredHeight);
        }

    public:
        virtual ~LayoutManager() = 0 {}

        inline const XMFLOAT2& getScroll() const {
            return scroll;
        }

        inline void setScroll(const XMFLOAT2& scroll) {
            this->scroll = scroll;
        }

        __declspec(property(get = getScroll, put = setScroll)) const XMFLOAT2& Scroll;

        virtual void scrollBy(ControlGroup& group, ChildrenProvider& provider, float dx, float dy) {}

        inline const XMFLOAT2& getMaxScroll() const {
            return maxScroll;
        }

        __declspec(property(get = getMaxScroll)) const XMFLOAT2& MaxScroll;

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