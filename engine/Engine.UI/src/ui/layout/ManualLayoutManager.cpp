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

            c->layout(c->Position.x, c->Position.y, c->Width.Value, c->Height.Value);
        }
    }
}