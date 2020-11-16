#include "LinearLayout.h"

namespace Ghurund::UI {
    bool LinearLayout::focusUp() {
        if (__super::focusUp())
            return true;
        if (Focusable)
            return false;
        size_t i = Children.Size - 1;
        if (i == 0)
            return true;
        if (focusedChild) {
            if (Orientation != Orientation::VERTICAL)
                return focusedChild->focusUp();
            i = Children.indexOf(focusedChild);
        }
        for (i; i != -1; i--) {
            if (Children[i]->focusUp())
                return true;
        }
        return false;
    }
    
    bool LinearLayout::focusDown() {
        if (__super::focusDown())
            return true;
        if (Focusable)
            return false;
        size_t i = 0;
        if (i == Children.Size - 1)
            return true;
        if (focusedChild) {
            if (Orientation != Orientation::VERTICAL)
                return focusedChild->focusDown();
            i = Children.indexOf(focusedChild);
        }
        for (i; i < Children.Size; i++) {
            if (Children[i]->focusDown())
                return true;
        }
        return false;
    }
    
    bool LinearLayout::focusLeft() {
        if (__super::focusLeft())
            return true;
        if (Focusable)
            return false;
        size_t i = Children.Size - 1;
        if (i == 0)
            return true;
        if (focusedChild) {
            if (Orientation != Orientation::HORIZONTAL)
                return focusedChild->focusLeft();
            i = Children.indexOf(focusedChild);
        }
        for (i; i != -1; i--) {
            if (Children[i]->focusLeft())
                return true;
        }
        return false;
    }
    
    bool LinearLayout::focusRight() {
        if (Orientation != Orientation::HORIZONTAL)
            return __super::focusRight();
        if (__super::focusRight())
            return true;
        if (Focusable)
            return false;
        size_t i = 0;
        if (i == Children.Size - 1)
            return true;
        if (focusedChild) {
            if (Orientation != Orientation::HORIZONTAL)
                return focusedChild->focusRight();
            i = Children.indexOf(focusedChild);
        }
        for (i; i < Children.Size; i++) {
            if (Children[i]->focusRight())
                return true;
        }
        return false;
    }
}
