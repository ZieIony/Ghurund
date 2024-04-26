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
                ConstraintSet& constraints = c->Parent->getConstraints(*c);
                dependencies.put(&constraints.Right);
                dependencies.put(&constraints.Width);
            }
        } else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
            for (ControlWithConstraints& c : ((ControlGroup&)control).Children) {
                dependencies.put(&c.Constraints.Right);
                dependencies.put(&c.Constraints.Width);
            }
        }
        ConstraintSet& constraints = control.Parent->getConstraints(control);
        dependencies.put(&constraints.Height);
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
                ConstraintSet& constraints = c->Parent->getConstraints(*c);
                dependencies.put(&constraints.Bottom);
                dependencies.put(&constraints.Height);
            }
        } else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
            for (ControlWithConstraints& c : ((ControlGroup&)control).Children) {
                dependencies.put(&c.Constraints.Bottom);
                dependencies.put(&c.Constraints.Height);
            }
        }
        ConstraintSet& constraints = control.Parent->getConstraints(control);
        dependencies.put(&constraints.Width);
    }

    void FlowHeightConstraint::evaluate() {
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
        evaluated = true;
    }
}