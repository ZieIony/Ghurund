#include "ghuipch.h"
#include "SiblingConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include <ui/control/ControlGroup.h>

namespace Ghurund::UI {
	bool SiblingLeftConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingLeftConstraint& c = (const SiblingLeftConstraint&)other;
		return name == c.name;
	}

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

	bool SiblingHeightConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingHeightConstraint& c = (const SiblingHeightConstraint&)other;
		return name == c.name;
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

	bool SiblingWidthConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingWidthConstraint& c = (const SiblingWidthConstraint&)other;
		return name == c.name;
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

	bool SiblingBottomConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingBottomConstraint& c = (const SiblingBottomConstraint&)other;
		return name == c.name;
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

	bool SiblingTopConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingTopConstraint& c = (const SiblingTopConstraint&)other;
		return name == c.name;
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

	bool SiblingRightConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingRightConstraint& c = (const SiblingRightConstraint&)other;
		return name == c.name;
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
