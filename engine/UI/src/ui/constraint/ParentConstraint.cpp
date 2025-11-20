#include "ghuipch.h"
#include "ParentConstraint.h"

#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ParentLeftConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ParentLeftConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& ParentRightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ParentRightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ParentRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		ConstraintSet& set = control.Parent->Parent->getConstraints(*control.Parent);
		dependencies.put(&set.Width);
		graph.add(this);
	}

	void ParentRightConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = (*dependencies.begin())->Value + offset;
		} else {
			value = offset;
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& ParentTopConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ParentTopConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& ParentBottomConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ParentBottomConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ParentBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		ConstraintSet& set = control.Parent->Parent->getConstraints(*control.Parent);
		dependencies.put(&set.Height);
		graph.add(this);
	}

	void ParentBottomConstraint::evaluate() {
		if (!dependencies.Empty) {
			value = (*dependencies.begin())->Value + offset;
		} else {
			value = offset;
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& ParentWidthConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ParentWidthConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ParentWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		
		parentWidth.set(&control.Parent->Parent->getConstraints(*control.Parent).Width);
		parentWidth->addReference();
		dependencies.put(parentWidth.get());

		contentWidth.set(&control.Parent->ContentSize.Width);
		contentWidth->addReference();
		dependencies.put(contentWidth.get());

		graph.add(this);
	}

	void ParentWidthConstraint::evaluate() {
		if (!dependencies.Empty) {
			float width = parentWidth->Evaluated ? parentWidth->Value : contentWidth->Value;
			value = minMax(min, width * ratio + offset, max);
		} else {
			value = minMax(min, offset, max);
		}
		evaluated = true;
	}

	const Ghurund::Core::Type& ParentHeightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ParentHeightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ParentHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;

		parentHeight.set(&control.Parent->Parent->getConstraints(*control.Parent).Height);
		parentHeight->addReference();
		dependencies.put(parentHeight.get());

		contentHeight.set(&control.Parent->ContentSize.Height);
		contentHeight->addReference();
		dependencies.put(contentHeight.get());

		graph.add(this);
	}
	
	void ParentHeightConstraint::evaluate() {
		if (!dependencies.Empty) {
			float height = parentHeight->Evaluated ? parentHeight->Value : contentHeight->Value;
			value = minMax(min, height * ratio + offset, max);
		} else {
			value = minMax(min, offset, max);
		}
		evaluated = true;
	}
}
