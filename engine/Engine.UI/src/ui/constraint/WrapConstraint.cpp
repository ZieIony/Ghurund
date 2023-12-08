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
				dependencies.put(&c->Left);
				dependencies.put(&c->Right);
			}
		} else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
			for (Control* c : ((ControlGroup&)control).Children) {
				dependencies.put(&c->Left);
				dependencies.put(&c->Right);
			}
		}
		this->control = &control;
	}

	void WrapWidthConstraint::evaluate() {
		value = control->MeasuredSize.Width;
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
				dependencies.put(&c->Top);
				dependencies.put(&c->Bottom);
			}
		} else if (control.Type.isOrExtends(ControlGroup::TYPE)) {
			for (Control* c : ((ControlGroup&)control).Children) {
				dependencies.put(&c->Top);
				dependencies.put(&c->Bottom);
			}
		}
		this->control = &control;
	}

	void WrapHeightConstraint::evaluate() {
		value = control->MeasuredSize.Height;
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
		evaluated = true;
	}
}