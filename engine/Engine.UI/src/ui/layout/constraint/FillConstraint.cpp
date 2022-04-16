#include "ghuipch.h"
#include "FillConstraint.h"

#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    void WidthFillConstraint::resolve(Control& control) {
        dependencies.add(&control.Parent->Width);
    }

    void WidthFillConstraint::evaluate() {
        value = (*dependencies.begin())->Value;
    }

    void HeightFillConstraint::resolve(Control& control) {
        dependencies.add(&control.Parent->Height);
    }

    void HeightFillConstraint::evaluate() {
        value = (*dependencies.begin())->Value;
    }
}
