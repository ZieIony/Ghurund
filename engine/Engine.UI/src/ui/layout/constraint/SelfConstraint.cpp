#include "ghuipch.h"
#include "SelfConstraint.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
    void SelfWidthConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        dependencies.clear();
        dependencies.add(&control.Width);
        constraints.add(this);
    }
    
    void SelfHeightConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        dependencies.clear();
        dependencies.add(&control.Height);
        constraints.add(this);
    }
    
    void CenterLeftConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        constraints.add(this);
        left->resolve(control, constraints);
        width->resolve(control, constraints);
        right->resolve(control, constraints);
    }
    
    void CenterRightConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        constraints.add(this);
        left->resolve(control, constraints);
        width->resolve(control, constraints);
        right->resolve(control, constraints);
    }
    
    void CenterTopConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        constraints.add(this);
        top->resolve(control, constraints);
        height->resolve(control, constraints);
        bottom->resolve(control, constraints);
    }
    
    void CenterBottomConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        constraints.add(this);
        top->resolve(control, constraints);
        height->resolve(control, constraints);
        bottom->resolve(control, constraints);
    }

    void LeftWidthConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        dependencies.clear();
        left = &control.Left;
        dependencies.add(&control.Left);
        width = &control.Width;
        dependencies.add(&control.Width);
        constraints.add(this);
    }

    void LeftRightConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        dependencies.clear();
        left = &control.Left;
        dependencies.add(&control.Left);
        right = &control.Right;
        dependencies.add(&control.Right);
        constraints.add(this);
    }

    void WidthRightConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        dependencies.clear();
        width = &control.Width;
        dependencies.add(&control.Width);
        right = &control.Right;
        dependencies.add(&control.Right);
        constraints.add(this);
    }

    void TopHeightConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        dependencies.clear();
        top = &control.Top;
        dependencies.add(&control.Top);
        height = &control.Height;
        dependencies.add(&control.Height);
        constraints.add(this);
    }

    void TopBottomConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        dependencies.clear();
        top = &control.Top;
        dependencies.add(&control.Top);
        bottom = &control.Bottom;
        dependencies.add(&control.Bottom);
        constraints.add(this);
    }

    void HeightBottomConstraint::resolve(Control& control, List<Constraint*>& constraints) {
        dependencies.clear();
        height = &control.Height;
        dependencies.add(&control.Height);
        bottom = &control.Bottom;
        dependencies.add(&control.Bottom);
        constraints.add(this);
    }
}