#include "ghuipch.h"
#include "WrapConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    bool WrapWidthConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const WrapWidthConstraint& c = (const WrapWidthConstraint&)other;
        return control == c.control;
    }

    void WrapWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
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
        this->control = &control;
    }

    void WrapWidthConstraint::evaluate() {
        value = control->MeasuredSize.Width;
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
    }

    bool WrapHeightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const WrapHeightConstraint& c = (const WrapHeightConstraint&)other;
        return control == c.control;
    }

    void WrapHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
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
        this->control = &control;
    }

    void WrapHeightConstraint::evaluate() {
        value = control->MeasuredSize.Height;
        for (Constraint* c : dependencies)
            value = std::max(value, c->Value);
        value = minMax(min, value * ratio + offset, max);
    }
}