#include "ghuipch.h"
#include "PreviousConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& PreviousLeftConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousLeftConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		Constraint& constraint = children[index - 1].Constraints.Left;
		dependencies.put(&constraint);
		graph.add(this);
	}

	void PreviousLeftConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = (*dependencies.begin())->Value + offset;
		} else {
			value = 0;
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& PreviousRightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousRightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		Constraint& constraint = children[index - 1].Constraints.Right;
		dependencies.put(&constraint);
		graph.add(this);
	}

	void PreviousRightConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = (*dependencies.begin())->Value + offset;
		} else {
			value = 0;
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& PreviousTopConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousTopConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		Constraint& constraint = children[index - 1].Constraints.Top;
		dependencies.put(&constraint);
		graph.add(this);
	}

	void PreviousTopConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = (*dependencies.begin())->Value + offset;
		} else {
			value = 0;
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& PreviousBottomConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousBottomConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		Constraint& constraint = children[index - 1].Constraints.Bottom;
		dependencies.put(&constraint);
		graph.add(this);
	}

	void PreviousBottomConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = (*dependencies.begin())->Value + offset;
		} else {
			value = 0;
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& PreviousWidthConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousWidthConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		Constraint& constraint = children[index - 1].Constraints.Width;
		dependencies.put(&constraint);
		graph.add(this);
	}

	void PreviousWidthConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		} else {
			value = minMax(min, offset, max);
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& PreviousHeightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PreviousHeightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PreviousHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		Constraint& constraint = children[index - 1].Constraints.Height;
		dependencies.put(&constraint);
		graph.add(this);
	}
	
	void PreviousHeightConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		} else {
			value = minMax(min, offset, max);
		}
		evaluated = true;
	}
}
