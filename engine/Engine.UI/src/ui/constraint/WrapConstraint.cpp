#include "ghuipch.h"
#include "WrapConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"
#include "ui/Canvas.h"
#include "ui/UIDebugTools.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& WrapWidthConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<WrapWidthConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool WrapWidthConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const WrapWidthConstraint& c = (const WrapWidthConstraint&)other;
		return control == c.control;
	}

	void WrapWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		graph.add(this);
		evaluated = false;
		dependencies.clear();
		if (control.Type.isOrExtends(ControlContainerBase::TYPE)) {
			Control* c = ((ControlContainerBase&)control).Child;
			if (c) {
				ConstraintSet& constraints = c->Parent->getConstraints(*c);
				dependencies.put(&constraints.Left);
				dependencies.put(&constraints.Width);
				dependencies.put(&constraints.Right);
			}
		} else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
			for (ControlWithConstraints& c : ((ControlGroup&)control).Children) {
				dependencies.put(&c.Constraints.Left);
				dependencies.put(&c.Constraints.Width);
				dependencies.put(&c.Constraints.Right);
			}
		}
		this->control = &control;
	}

	void WrapWidthConstraint::evaluate() {
#ifdef _DEBUG
		bool prevZero = value == 0;
#endif
		value = control->ContentSize.Width;
		if (dependencies.Size > 0) {
			float left = std::numeric_limits<float>::max();
			float right = std::numeric_limits<float>::lowest();
			for (Constraint* c : dependencies) {
				if (c->Evaluated) {
					left = std::min(left, c->Value);
					right = std::max(right, c->Value);
				}
			}
			value = std::max(value, right - left);
		}
		value = minMax(min, value * ratio + offset, max);
#ifdef _DEBUG
		if (value == 0 && (!prevZero || firstEvaluation)) {
			AString name = control->Name ? *control->Name : "[unnamed]";
			auto message = std::format(_T("Control's ({}: {}) wrap width evaluates to 0\n"), control->Type.Name, name);
			Logger::log(LogType::INFO, message.c_str());
		}
#endif
		firstEvaluation = false;
		evaluated = true;
	}

	const Ghurund::Core::Type& WrapHeightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<WrapHeightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool WrapHeightConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const WrapHeightConstraint& c = (const WrapHeightConstraint&)other;
		return control == c.control;
	}

	void WrapHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		graph.add(this);
		evaluated = false;
		dependencies.clear();
		if (control.Type.isOrExtends(ControlContainerBase::TYPE)) {
			Control* c = ((ControlContainerBase&)control).Child;
			if (c) {
				ConstraintSet& constraints = c->Parent->getConstraints(*c);
				dependencies.put(&constraints.Top);
				dependencies.put(&constraints.Height);
				dependencies.put(&constraints.Bottom);
			}
		} else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
			for (ControlWithConstraints& c : ((ControlGroup&)control).Children) {
				dependencies.put(&c.Constraints.Top);
				dependencies.put(&c.Constraints.Height);
				dependencies.put(&c.Constraints.Bottom);
			}
		}
		this->control = &control;
	}

	void WrapHeightConstraint::evaluate() {
#ifdef _DEBUG
		bool prevZero = value == 0;
#endif
		value = control->ContentSize.Height;
		if (dependencies.Size > 0) {
			float top = std::numeric_limits<float>::max();
			float bottom = std::numeric_limits<float>::lowest();
			for (Constraint* c : dependencies) {
				if (c->Evaluated) {
					top = std::min(top, c->Value);
					bottom = std::max(bottom, c->Value);
				}
			}
			value = std::max(value, bottom - top);
		}
		value = minMax(min, value * ratio + offset, max);
#ifdef _DEBUG
		if (value == 0 && (!prevZero || firstEvaluation)) {
			AString name = control->Name ? *control->Name : "[unnamed]";
			auto message = std::format(_T("Control's ({}: {}) wrap height evaluates to 0\n"), control->Type.Name, name);
			Logger::log(LogType::INFO, message.c_str());
		}
#endif
		firstEvaluation = false;
		evaluated = true;
	}
}