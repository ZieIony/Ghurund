#include "ghuipch.h"
#include "ParentConstraint.h"

#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ParentLeftConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParentLeftConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& ParentRightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParentRightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ParentRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        evaluated = false;
        dependencies.put(&control.Parent->Width);
        graph.add(this);
    }

    const Ghurund::Core::Type& ParentTopConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParentTopConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& ParentBottomConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParentBottomConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ParentBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        evaluated = false;
        dependencies.put(&control.Parent->Height);
        graph.add(this);
    }

    const Ghurund::Core::Type& ParentWidthConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParentWidthConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ParentWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        evaluated = false;
        dependencies.put(&control.Parent->Width);
        graph.add(this);
    }
    
    const Ghurund::Core::Type& ParentHeightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParentHeightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ParentHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        evaluated = false;
        dependencies.put(&control.Parent->Height);
        graph.add(this);
    }
}
