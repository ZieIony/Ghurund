#include "ghuipch.h"
#include "StackLayoutManager.h"

namespace Ghurund::UI {
    const FloatSize StackLayoutManager::measure(float parentWidth, float parentHeight) {
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            c->measure(parentWidth, parentHeight);
        }
        return { parentWidth, parentHeight };
    }

    void StackLayoutManager::layout(float x, float y, float width, float height) {
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            auto pos = c->Position;
            c->layout(
                c->Left.Value,
                c->Top.Value,
                c->Width.Value,
                c->Height.Value
            );
        }
    }
}