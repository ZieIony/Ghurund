#pragma once

#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class LayoutManager {
    protected:
        inline float measureMaxWidth(ControlGroup& group) {
            float measuredWidth = 0;
            if (group.PreferredSize.width == PreferredSize::Width::WRAP) {
                for (Control* c : group.Children)
                    measuredWidth = std::max(measuredWidth, (float)c->MeasuredSize.width);
            } else if (group.PreferredSize.width != PreferredSize::Width::FILL) {
                measuredWidth = (float)group.PreferredSize.width;
            }
            return measuredWidth;
        }

        inline float measureMaxHeight(ControlGroup& group) {
            float measuredHeight = 0;
            if (group.PreferredSize.height == PreferredSize::Height::WRAP) {
                for (Control* c : group.Children)
                    measuredHeight = std::max(measuredHeight, (float)c->MeasuredSize.height);
            } else if (group.PreferredSize.height != PreferredSize::Height::FILL) {
                measuredHeight = (float)group.PreferredSize.height;
            }
            return measuredHeight;
        }

    public:
        virtual ~LayoutManager() = 0 {}

        virtual FloatSize measure(ControlGroup& group, float parentWidth, float parentHeight) {
            for (Control* c : group.Children) {
                c->measure(
                    group.PreferredSize.width >= 0 ? group.PreferredSize.width : parentWidth,
                    group.PreferredSize.height >= 0 ? group.PreferredSize.height : parentHeight
                );
            }
            return { 0,0 };
        }

        virtual void layout(ControlGroup& group, float x, float y, float width, float height) = 0;
    };

    template<class T, class ControlType>
    class AdapterView;

    template<class T, class ControlType>
    requires IsControl<ControlType>
    class AdapterLayoutManager {
    protected:
        XMFLOAT2 scroll = { 0,0 };

    public:
        virtual ~AdapterLayoutManager() = 0 {}

        inline const XMFLOAT2& getScroll() const {
            return scroll;
        }

        __declspec(property(get = getScroll)) XMFLOAT2& Scroll;

        virtual void scrollBy(AdapterView<T, ControlType>& adapterView, float dx, float dy) {}

        virtual const FloatSize measure(AdapterView<T, ControlType>& adapterView) = 0;

        virtual void layout(AdapterView<T, ControlType>& adapterView, float x, float y, float width, float height) = 0;
    };

}