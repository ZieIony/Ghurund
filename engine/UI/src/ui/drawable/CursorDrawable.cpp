#include "ghuipch.h"
#include "CursorDrawable.h"

#include "core/Color.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    void CursorDrawable::draw(ICanvas& canvas, const Ghurund::Core::FloatSize& size, const Ghurund::UI::Color& tint) const {
        if (visible) {
            canvas.Color = lerp(tint, color, tint.A);
            canvas.fillRect(0, 0, size.Width, size.Height);
        }
        owner->repaint();
    }
}
