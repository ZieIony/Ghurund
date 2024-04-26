#pragma once

#include "ui/control/Control.h"

namespace Ghurund::UI {
	struct ControlWithConstraints {
	private:
		ConstraintSet constraints;

	public:
		SharedPointer<Control> control;

		ControlWithConstraints(Control* control, const ConstraintSet& constraints):control(SharedPointer(control)), constraints(constraints) {
			control->addReference();
		}

		ControlWithConstraints(SharedPointer<Control>& control, const ConstraintSet& constraints):control(control), constraints(constraints) {}

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