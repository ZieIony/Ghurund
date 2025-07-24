#pragma once

#include "core/object/IntrusivePointer.h"
#include "ui/control/Control.h"
#include "ui/constraint/ConstraintSet.h"

namespace Ghurund::UI {
	struct ControlWithConstraints {
	private:
		ConstraintSet constraints;

	public:
		IntrusivePointer<Control> control;

		ControlWithConstraints(Control* control, const ConstraintSet& constraints):control(IntrusivePointer(control)), constraints(constraints) {
			control->addReference();
		}

		ControlWithConstraints(IntrusivePointer<Control>& control, const ConstraintSet& constraints):control(control), constraints(constraints) {}

		inline bool operator==(const ControlWithConstraints& other) const {
			return control == other.control && constraints == other.constraints;
		}

		inline ConstraintSet& getConstraints() {
			return constraints;
		}

		inline void setConstraints(const ConstraintSet& constraints) {
			this->constraints = constraints;
		}

		__declspec(property(get = getConstraints, put = setConstraints)) ConstraintSet& Constraints;
	};
}