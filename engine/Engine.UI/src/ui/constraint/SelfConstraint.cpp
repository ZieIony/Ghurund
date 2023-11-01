#include "ghuipch.h"
#include "SelfConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    void SelfWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.put(&control.Width);
        graph.add(this);
    }

    void SelfHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.put(&control.Height);
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
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
    }

    void LeftRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        left->resolve(control, graph);
        right->resolve(control, graph);
    }

    void WidthRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }

    void TopHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
    }

    void TopBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        top->resolve(control, graph);
        bottom->resolve(control, graph);
    }

    void HeightBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }
}