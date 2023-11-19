#include "ghuipch.h"
#include "WindowConstraint.h"

namespace Ghurund::UI {
    bool WindowWidthConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const WindowWidthConstraint& c = (const WindowWidthConstraint&)other;
        return window == c.window;
    }

    bool WindowHeightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const WindowHeightConstraint& c = (const WindowHeightConstraint&)other;
        return window == c.window;
    }
}