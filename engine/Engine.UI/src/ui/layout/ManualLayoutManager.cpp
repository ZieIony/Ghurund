#include "ghuipch.h"
#include "ManualLayoutManager.h"

namespace Ghurund::UI {
    const Ghurund::Core::FloatSize ManualLayoutManager::measure(float parentWidth, float parentHeight) {
        __super::measure(parentWidth, parentHeight);
        return { measureMaxWidth(), measureMaxHeight() };
    }

    void ManualLayoutManager::layout(float x, float y, float width, float height) {
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;

            c->layout(c->Position.x, c->Position.y,
                c->PreferredSize.width == PreferredSize::Width::FILL ? width : c->MeasuredSize.width,
                c->PreferredSize.height == PreferredSize::Height::FILL ? height : c->MeasuredSize.height
            );
        }
    }
}