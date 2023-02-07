#include "ghuipch.h"
#include "SelfConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    void SelfWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.add(&control.Width);
        graph.add(this);
    }
    
    void SelfHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.add(&control.Height);
        graph.add(this);
    }
    
    void CenterLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }
    
    void CenterRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }
    
    void CenterTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }
    
    void CenterBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }

    void LeftWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        left.set(&control.Left);
        dependencies.add(&control.Left);
        width.set(&control.Width);
        dependencies.add(&control.Width);
        graph.add(this);
    }

    void LeftRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        left.set(&control.Left);
        dependencies.add(&control.Left);
        right.set(&control.Right);
        dependencies.add(&control.Right);
        graph.add(this);
    }

    void WidthRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        width.set(&control.Width);
        dependencies.add(&control.Width);
        right.set(&control.Right);
        dependencies.add(&control.Right);
        graph.add(this);
    }

    void TopHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        top.set(&control.Top);
        dependencies.add(&control.Top);
        height.set(&control.Height);
        dependencies.add(&control.Height);
        graph.add(this);
    }

    void TopBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        top.set(&control.Top);
        dependencies.add(&control.Top);
        bottom.set(&control.Bottom);
        dependencies.add(&control.Bottom);
        graph.add(this);
    }

    void HeightBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        height.set(&control.Height);
        dependencies.add(&control.Height);
        bottom.set(&control.Bottom);
        dependencies.add(&control.Bottom);
        graph.add(this);
    }
}