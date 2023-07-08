#include "ghuipch.h"
#include "SiblingConstraint.h"

#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
	void SiblingLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		Control* ref = control.Parent->find(name, false);
		if (ref) {
			dependencies.add(&ref->Left);
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
		Control* ref = control.Parent->find(name, false);
		if (ref) {
			dependencies.add(&ref->Height);
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
		Control* ref = control.Parent->find(name, false);
		if (ref) {
			dependencies.add(&ref->Width);
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
		Control* ref = control.Parent->find(name, false);
		if (ref) {
			dependencies.add(&ref->Bottom);
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
		Control* ref = control.Parent->find(name, false);
		if (ref) {
			dependencies.add(&ref->Top);
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
		Control* ref = control.Parent->find(name, false);
		if (ref) {
			dependencies.add(&ref->Right);
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
