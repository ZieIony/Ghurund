#include "ghuipch.h"
#include "ParentConstraint.h"

#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
    void ParentRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.put(&control.Parent->Width);
        graph.add(this);
    }
    
    void ParentBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.put(&control.Parent->Height);
        graph.add(this);
    }
    
    void ParentWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.put(&control.Parent->Width);
        graph.add(this);
    }
    
    void ParentHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.put(&control.Parent->Height);
        graph.add(this);
    }
}
