#include "ghuipch.h"
#include "CursorDrawable.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
    void CursorDrawable::onDraw(ICanvas& canvas, const Ghurund::Core::FloatSize& size) const {
        if (visible) {
            canvas.Color = color;
            canvas.fillRect(0, 0, size.Width, size.Height);
        }
        owner->repaint();
    }
}
