#include "ghuipch.h"
#include "CursorDrawable.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
    void CursorDrawable::onDraw(ICanvas& canvas) {
        if (visible)
            canvas.fillRect(0, 0, size.Width, size.Height, color);
        owner->repaint();
    }
}
