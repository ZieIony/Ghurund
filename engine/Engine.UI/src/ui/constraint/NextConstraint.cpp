#include "ghuipch.h"
#include "NextConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include <ui/control/ControlGroup.h>

namespace Ghurund::UI {

	void NextLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void NextRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void NextTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void NextBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void NextWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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

	void NextHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
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
