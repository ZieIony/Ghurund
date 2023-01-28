#include "ghuipch.h"
#include "SiblingConstraint.h"

#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
    void SiblingLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.add(&control.Parent->find(name, false)->Left);
        graph.add(this);
    }
    
    void SiblingHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.add(&control.Parent->find(name, false)->Height);
        graph.add(this);
    }
    
    void SiblingWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.add(&control.Parent->find(name, false)->Width);
        graph.add(this);
    }
    
    void SiblingBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.add(&control.Parent->find(name, false)->Bottom);
        graph.add(this);
    }
    
    void SiblingTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.add(&control.Parent->find(name, false)->Top);
        graph.add(this);
    }
    
    void SiblingRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.add(&control.Parent->find(name, false)->Right);
        graph.add(this);
    }
}
