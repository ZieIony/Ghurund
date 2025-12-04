#include "ghuipch.h"
#include "PreviousSpringConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& PreviousSpringLeftConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousSpringLeftConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousSpringLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		ControlWithConstraints& ref = children[index - 1];
		dependencies.put(&ref.Constraints.Left);
		graph.add(this);
	}

	const Ghurund::Core::Type& PreviousSpringRightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousSpringRightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousSpringRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		ControlWithConstraints& ref = children[index - 1];
		dependencies.put(&ref.Constraints.Right);
		graph.add(this);
	}

	const Ghurund::Core::Type& PreviousSpringTopConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousSpringTopConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousSpringTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		ControlWithConstraints& ref = children[index - 1];
		dependencies.put(&ref.Constraints.Top);
		graph.add(this);
	}

	const Ghurund::Core::Type& PreviousSpringBottomConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousSpringBottomConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousSpringBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		ControlWithConstraints& ref = children[index - 1];
		dependencies.put(&ref.Constraints.Bottom);
		graph.add(this);
	}
}
