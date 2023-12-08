#include "ghuipch.h"
#include "PreviousConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include <ui/control/ControlGroup.h>

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
		size_t index = children.indexOf(&control);
		Control* ref = children[index - 1];
		if (index == children.Size || index == 0) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Previous' not found.\n"));
		} else {
			dependencies.put(&ref->Left);
			graph.add(this);
		}
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
		size_t index = children.indexOf(&control);
		Control* ref = children[index - 1];
		if (index == children.Size || index == 0) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Previous' not found.\n"));
		} else {
			dependencies.put(&ref->Right);
			graph.add(this);
		}
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
		size_t index = children.indexOf(&control);
		Control* ref = children[index - 1];
		if (index == children.Size || index == 0) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Previous' not found.\n"));
		} else {
			dependencies.put(&ref->Top);
			graph.add(this);
		}
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
		size_t index = children.indexOf(&control);
		Control* ref = children[index - 1];
		if (index == children.Size || index == 0) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Previous' not found.\n"));
		} else {
			dependencies.put(&ref->Bottom);
			graph.add(this);
		}
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
		size_t index = children.indexOf(&control);
		Control* ref = children[index - 1];
		if (index == children.Size || index == 0) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Previous' not found.\n"));
		} else {
			dependencies.put(&ref->Width);
			graph.add(this);
		}
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
		size_t index = children.indexOf(&control);
		Control* ref = children[index - 1];
		if (index == children.Size || index == 0) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Previous' not found.\n"));
		} else {
			dependencies.put(&ref->Height);
			graph.add(this);
		}
	}
}
