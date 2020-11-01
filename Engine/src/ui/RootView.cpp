#include "RootView.h"

namespace Ghurund::UI {
    bool RootView::dispatchKeyEvent(const KeyEventArgs& event) {
        if (__super::dispatchKeyEvent(event))
            return true;

        if (event.Key == VK_TAB && event.Action == KeyAction::DOWN) {
            if (GetKeyState(VK_SHIFT) & 0x8000) {
                if (!focusPrevious() && Focus) {
                    clearFocus();
                    focusPrevious();
                }
            } else {
                if (!focusNext() && Focus) {
                    clearFocus();
                    focusNext();
                }
            }
            return true;
        }

        if (event.Key == VK_ESCAPE && event.Action == KeyAction::DOWN) {
            clearFocus();
            return true;
        }

        return false;
    }
}
