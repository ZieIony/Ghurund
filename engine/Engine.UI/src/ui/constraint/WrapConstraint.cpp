#include "ghuipch.h"
#include "WrapConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    void WrapWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        dependencies.clear();
        if (control.Type.isOrExtends(ControlContainer::TYPE)) {
            Control* c = ((ControlContainer&)control).Child;
            if (c) {
                dependencies.add(&c->Right);
                dependencies.add(&c->Width);
            }
        } else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
            for (Control* c : ((ControlGroup&)control).Children) {
                dependencies.add(&c->Right);
                dependencies.add(&c->Width);
            }
        }
        this->control = &control;
    }

    void WrapWidthConstraint::evaluate() {
        value = control->MeasuredSize.Width;
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
    }

    void WrapHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        dependencies.clear();
        if (control.Type.isOrExtends(ControlContainer::TYPE)) {
            Control* c = ((ControlContainer&)control).Child;
            if (c) {
                dependencies.add(&c->Bottom);
                dependencies.add(&c->Height);
            }
        } else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
            for (Control* c : ((ControlGroup&)control).Children) {
                dependencies.add(&c->Bottom);
                dependencies.add(&c->Height);
            }
        }
        this->control = &control;
    }

    void WrapHeightConstraint::evaluate() {
        value = control->MeasuredSize.Height;
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
    }
}