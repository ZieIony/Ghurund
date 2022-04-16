#include "ghuipch.h"
#include "Constraint.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
    void LeftWidthConstraint::resolve(Control& control) {
        dependencies.clear();
        left = &control.Left;
        dependencies.add(&control.Left);
        width = &control.Width;
        dependencies.add(&control.Width);
    }

    void RightWidthConstraint::resolve(Control& control) {
        dependencies.clear();
        right = &control.Right;
        dependencies.add(&control.Right);
        width = &control.Width;
        dependencies.add(&control.Width);
    }

    void TopHeightConstraint::resolve(Control& control) {
        dependencies.clear();
        top = &control.Top;
        dependencies.add(&control.Top);
        height = &control.Height;
        dependencies.add(&control.Height);
    }

    void BottomHeightConstraint::resolve(Control& control) {
        dependencies.clear();
        bottom = &control.Bottom;
        dependencies.add(&control.Bottom);
        height = &control.Height;
        dependencies.add(&control.Height);
    }
}
