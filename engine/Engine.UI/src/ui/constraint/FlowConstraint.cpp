#include "ghuipch.h"
#include "FlowConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    void FlowWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
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
        dependencies.add(&control.Height);
    }

    void FlowWidthConstraint::evaluate() {
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
    }

    void FlowHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
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
        dependencies.add(&control.Width);
    }

    void FlowHeightConstraint::evaluate() {
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
    }
}