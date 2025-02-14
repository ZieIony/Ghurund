#pragma once

#include "core/IntrusivePointer.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/constraint/ValueConstraint.h"

namespace UnitTest::Utils {

    template<class Control>
    inline void layoutControl(Ghurund::Core::IntrusivePointer<Control>& control, float width, float height) {
        auto widthConstraint = Ghurund::Core::makeIntrusive<Ghurund::UI::ValueConstraint>(width);
        auto heightConstraint = Ghurund::Core::makeIntrusive<Ghurund::UI::ValueConstraint>(height);
        Ghurund::UI::ConstraintGraph graph;
        control->resolveConstraints(graph, *widthConstraint.get(), *heightConstraint.get());
        graph.sort();
        graph.evaluate();
        control->layout(0, 0, width, height);
    }
}