#include "ghuipch.h"
#include "ManualLayoutManager.h"

namespace Ghurund::UI {
    const FloatSize ManualLayoutManager::measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) {
        __super::measure(group, provider, parentWidth, parentHeight);
        return { measureMaxWidth(group), measureMaxHeight(group) };
    }

    void ManualLayoutManager::layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) {
        for (Control* c : group.Children) {
            if (!c->Visible)
                continue;

            c->layout(c->Position.x, c->Position.y,
                c->PreferredSize.width == PreferredSize::Width::FILL ? width : c->MeasuredSize.width,
                c->PreferredSize.height == PreferredSize::Height::FILL ? height : c->MeasuredSize.height
            );
        }
    }
}