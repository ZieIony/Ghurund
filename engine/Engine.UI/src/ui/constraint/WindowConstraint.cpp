#include "ghuipch.h"
#include "WindowConstraint.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& WindowWidthConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<WindowWidthConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool WindowWidthConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const WindowWidthConstraint& c = (const WindowWidthConstraint&)other;
        return window == c.window;
    }

    const Ghurund::Core::Type& WindowHeightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<WindowHeightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool WindowHeightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const WindowHeightConstraint& c = (const WindowHeightConstraint&)other;
        return window == c.window;
    }
}