#include "ghuipch.h"
#include "WrapConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& WrapWidthConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<WrapWidthConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
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
				dependencies.put(&c->ContentSize.Width);
			}
		} else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
			for (ControlWithConstraints& c : ((ControlGroup&)control).Children) {
				dependencies.put(&c.Constraints.Left);
				dependencies.put(&c.Constraints.Width);
				dependencies.put(&c.Constraints.Right);
				dependencies.put(&c.control->ContentSize.Width);
			}
		}
	}

	void WrapWidthConstraint::evaluate() {
		value = 0;
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
		firstEvaluation = false;
#endif
		evaluated = true;
	}

	const Ghurund::Core::Type& WrapHeightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<WrapHeightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
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
				dependencies.put(&c->ContentSize.Height);
			}
		} else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
			for (ControlWithConstraints& c : ((ControlGroup&)control).Children) {
				dependencies.put(&c.Constraints.Top);
				dependencies.put(&c.Constraints.Height);
				dependencies.put(&c.Constraints.Bottom);
				dependencies.put(&c.control->ContentSize.Height);
			}
		}
	}

	void WrapHeightConstraint::evaluate() {
		value = 0;
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
		firstEvaluation = false;
#endif
		evaluated = true;
	}
}