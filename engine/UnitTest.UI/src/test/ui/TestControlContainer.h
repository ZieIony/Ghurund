#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/constraint/ConstraintGraph.h"

namespace UnitTest {
	using namespace Ghurund::UI;

	class TestControlContainer:public ControlContainer {
	private:
		SharedPointer<ValueConstraint> widthConstraint = makeShared<ValueConstraint>(1000.0f);
		SharedPointer<ValueConstraint> heightConstraint = makeShared<ValueConstraint>(800.0f);

	public:
		void resolveConstraints() {
			ConstraintGraph graph;
			__super::resolveConstraints(graph, *widthConstraint.get(), *heightConstraint.get());
			graph.sort();
			graph.evaluate();
		}
	};
}