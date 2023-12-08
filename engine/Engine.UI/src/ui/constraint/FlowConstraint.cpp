#include "ghuipch.h"
#include "FlowConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& FlowWidthConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<FlowWidthConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void FlowWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        evaluated = false;
        dependencies.clear();
        if (control.Type.isOrExtends(ControlContainer::TYPE)) {
            Control* c = ((ControlContainer&)control).Child;
            if (c) {
                dependencies.put(&c->Right);
                dependencies.put(&c->Width);
            }
        } else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
            for (Control* c : ((ControlGroup&)control).Children) {
                dependencies.put(&c->Right);
                dependencies.put(&c->Width);
            }
        }
        dependencies.put(&control.Height);
    }

    void FlowWidthConstraint::evaluate() {
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
        evaluated = true;
    }

    const Ghurund::Core::Type& FlowHeightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<FlowHeightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void FlowHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        evaluated = false;
        dependencies.clear();
        if (control.Type.isOrExtends(ControlContainer::TYPE)) {
            Control* c = ((ControlContainer&)control).Child;
            if (c) {
                dependencies.put(&c->Bottom);
                dependencies.put(&c->Height);
            }
        } else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
            for (Control* c : ((ControlGroup&)control).Children) {
                dependencies.put(&c->Bottom);
                dependencies.put(&c->Height);
            }
        }
        dependencies.put(&control.Width);
    }

    void FlowHeightConstraint::evaluate() {
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
        evaluated = true;
    }
}