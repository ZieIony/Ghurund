#include "ghuipch.h"
#include "SiblingConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include <ui/control/ControlGroup.h>

namespace Ghurund::UI {
	void SiblingLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		Control* ref = ((ControlGroup*)control.Parent)->Children.find(name);
		if (ref) {
			dependencies.put(&ref->Left);
			graph.add(this);
		} else {
			auto text = std::format(
				_T("Constraint reference '{}' not found.\n"),
				name
			);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	void SiblingHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		Control* ref = ((ControlGroup*)control.Parent)->Children.find(name);
		if (ref) {
			dependencies.put(&ref->Height);
			graph.add(this);
		} else {
			auto text = std::format(
				_T("Constraint reference '{}' not found.\n"),
				name
			);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	void SiblingWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		Control* ref = ((ControlGroup*)control.Parent)->Children.find(name);
		if (ref) {
			dependencies.put(&ref->Width);
			graph.add(this);
		} else {
			auto text = std::format(
				_T("Constraint reference '{}' not found.\n"),
				name
			);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	void SiblingBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		Control* ref = ((ControlGroup*)control.Parent)->Children.find(name);
		if (ref) {
			dependencies.put(&ref->Bottom);
			graph.add(this);
		} else {
			auto text = std::format(
				_T("Constraint reference '{}' not found.\n"),
				name
			);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	void SiblingTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		Control* ref = ((ControlGroup*)control.Parent)->Children.find(name);
		if (ref) {
			dependencies.put(&ref->Top);
			graph.add(this);
		} else {
			auto text = std::format(
				_T("Constraint reference '{}' not found.\n"),
				name
			);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	void SiblingRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		Control* ref = ((ControlGroup*)control.Parent)->Children.find(name);
		if (ref) {
			dependencies.put(&ref->Right);
			graph.add(this);
		} else {
			auto text = std::format(
				_T("Constraint reference '{}' not found.\n"),
				name
			);
			Logger::log(LogType::WARNING, text.c_str());
		}

	}
}
