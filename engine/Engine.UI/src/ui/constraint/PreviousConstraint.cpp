#include "ghuipch.h"
#include "PreviousConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include <ui/control/ControlGroup.h>

namespace Ghurund::UI {

	void PreviousLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void PreviousRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void PreviousTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void PreviousBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void PreviousWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void PreviousHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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
