#include "ghuipch.h"
#include "WindowFrame.h"

#include "ui/Cursor.h"

namespace Ghurund::UI {
    bool WindowFrame::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (!__super::dispatchMouseMotionEvent(event)) {
            auto& pos = event.Position;
            if (pos.x < Padding.left && pos.y < Padding.top || pos.x >= Size.Width - Padding.right && pos.y >= Size.Height - Padding.bottom) {
                Cursor::SIZENWSE.set();
                return true;
            } else if (pos.x >= Size.Width - Padding.right && pos.y < Padding.top || pos.x < Padding.left && pos.y >= Size.Height - Padding.bottom) {
                Cursor::SIZENESW.set();
                return true;
            } else if (pos.x < Padding.left || pos.x >= Size.Width - Padding.right) {
                Cursor::SIZEWE.set();
                return true;
            } else if (pos.y < Padding.top || pos.y > Size.Height - Padding.bottom) {
                Cursor::SIZENS.set();
                return true;
            }
        }
        return false;
    }
}
