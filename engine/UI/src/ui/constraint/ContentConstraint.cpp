#include "ghuipch.h"
#include "ContentConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ContentWidthConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ContentWidthConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ContentWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		graph.add(this);
		evaluated = false;
		dependencies.clear();
		dependencies.put(&control.ContentSize.Width);
	}

	void ContentWidthConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		} else {
			value = minMax(min, offset, max);
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& ContentHeightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ContentHeightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ContentHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		graph.add(this);
		evaluated = false;
		dependencies.clear();
		dependencies.put(&control.ContentSize.Height);
	}
	
	void ContentHeightConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		} else {
			value = minMax(min, offset, max);
		}
		evaluated = true;
	}
}