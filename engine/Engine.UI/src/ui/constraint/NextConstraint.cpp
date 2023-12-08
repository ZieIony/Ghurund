#include "ghuipch.h"
#include "NextConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include <ui/control/ControlGroup.h>

namespace Ghurund::UI {
	const Ghurund::Core::Type& NextLeftConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<NextLeftConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void NextLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.indexOf(&control);
		Control* ref = children[index + 1];
		if (index == children.Size || index == children.Size - 1) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Next' not found.\n"));
		} else {
			dependencies.put(&ref->Left);
			graph.add(this);
		}
	}

	const Ghurund::Core::Type& NextRightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<NextRightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void NextRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.indexOf(&control);
		Control* ref = children[index + 1];
		if (index == children.Size || index == children.Size - 1) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Next' not found.\n"));
		} else {
			dependencies.put(&ref->Right);
			graph.add(this);
		}
	}

	const Ghurund::Core::Type& NextTopConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<NextTopConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void NextTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.indexOf(&control);
		Control* ref = children[index + 1];
		if (index == children.Size || index == children.Size - 1) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Next' not found.\n"));
		} else {
			dependencies.put(&ref->Top);
			graph.add(this);
		}
	}

	const Ghurund::Core::Type& NextBottomConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<NextBottomConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void NextBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.indexOf(&control);
		Control* ref = children[index + 1];
		if (index == children.Size || index == children.Size - 1) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Next' not found.\n"));
		} else {
			dependencies.put(&ref->Bottom);
			graph.add(this);
		}
	}

	const Ghurund::Core::Type& NextWidthConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<NextWidthConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void NextWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.indexOf(&control);
		Control* ref = children[index + 1];
		if (index == children.Size || index == children.Size - 1) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Next' not found.\n"));
		} else {
			dependencies.put(&ref->Width);
			graph.add(this);
		}
	}

	const Ghurund::Core::Type& NextHeightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<NextHeightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void NextHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.indexOf(&control);
		Control* ref = children[index - 1];
		if (index == children.Size || index == 0) {
			Logger::log(LogType::WARNING, _T("Constraint reference 'Next' not found.\n"));
		} else {
			dependencies.put(&ref->Height);
			graph.add(this);
		}
	}
}
