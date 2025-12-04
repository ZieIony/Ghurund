#include "ghuipch.h"
#include "SiblingConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& SiblingLeftConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SiblingLeftConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool SiblingLeftConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingLeftConstraint& c = (const SiblingLeftConstraint&)other;
		return name == c.name;
	}

	void SiblingLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(name);
		if (index != children.Size) {
			auto left = &control.Parent->getConstraints(*children[index].control.get()).Left;
			dependencies.put(left);
			graph.add(this);
		} else {
			auto text = std::format(_T("Constraint reference '{}' not found.\n"), name);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	const Ghurund::Core::Type& SiblingHeightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SiblingHeightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool SiblingHeightConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingHeightConstraint& c = (const SiblingHeightConstraint&)other;
		return name == c.name;
	}

	void SiblingHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(name);
		if (index != children.Size) {
			auto height = &control.Parent->getConstraints(*children[index].control.get()).Height;
			dependencies.put(height);
			graph.add(this);
		} else {
			auto text = std::format(_T("Constraint reference '{}' not found.\n"), name);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	const Ghurund::Core::Type& SiblingWidthConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SiblingWidthConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool SiblingWidthConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingWidthConstraint& c = (const SiblingWidthConstraint&)other;
		return name == c.name;
	}

	void SiblingWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(name);
		if (index != children.Size) {
			auto width = &control.Parent->getConstraints(*children[index].control.get()).Width;
			dependencies.put(width);
			graph.add(this);
		} else {
			auto text = std::format(_T("Constraint reference '{}' not found.\n"), name);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	const Ghurund::Core::Type& SiblingBottomConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SiblingBottomConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool SiblingBottomConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingBottomConstraint& c = (const SiblingBottomConstraint&)other;
		return name == c.name;
	}

	void SiblingBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(name);
		if (index != children.Size) {
			auto bottom = &control.Parent->getConstraints(*children[index].control.get()).Bottom;
			dependencies.put(bottom);
			graph.add(this);
		} else {
			auto text = std::format(_T("Constraint reference '{}' not found.\n"), name);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	const Ghurund::Core::Type& SiblingTopConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SiblingTopConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool SiblingTopConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingTopConstraint& c = (const SiblingTopConstraint&)other;
		return name == c.name;
	}

	void SiblingTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(name);
		if (index != children.Size) {
			auto top = &control.Parent->getConstraints(*children[index].control.get()).Top;
			dependencies.put(top);
			graph.add(this);
		} else {
			auto text = std::format(_T("Constraint reference '{}' not found.\n"), name);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}

	const Ghurund::Core::Type& SiblingRightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SiblingRightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool SiblingRightConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const SiblingRightConstraint& c = (const SiblingRightConstraint&)other;
		return name == c.name;
	}

	void SiblingRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(name);
		if (index != children.Size) {
			auto right = &control.Parent->getConstraints(*children[index].control.get()).Right;
			dependencies.put(right);
			graph.add(this);
		} else {
			auto text = std::format(_T("Constraint reference '{}' not found.\n"), name);
			Logger::log(LogType::WARNING, text.c_str());
		}

	}
}
