#include "ghuipch.h"
#include "SpringSizeConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include <ui/control/ControlGroup.h>

namespace Ghurund::UI {
	const Ghurund::Core::Type& SpringWidthConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SpringWidthConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void SpringWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
		totalWeight = 0.0f;
		dependencies.clear();
		evaluated = false;
		ConstraintSet& set = control.Parent->Parent->getConstraints(*control.Parent);
		parentWidth.set(&set.Width);
		set.Width.addReference();
		auto& children = ((ControlGroup*)control.Parent)->Children;
		for (ControlWithConstraints& c : children) {
			if (c.Constraints.Width.Type.isOrExtends(SpringWidthConstraint::TYPE)) {
				totalWeight += ((SpringWidthConstraint&)c.Constraints.Width).Weight;
			} else {
				dependencies.put(&c.Constraints.Width);
			}
		}
		graph.add(this);
	}

	const Ghurund::Core::Type& SpringHeightConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SpringHeightConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void SpringHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
		dependencies.clear();
		evaluated = false;
		auto& children = ((ControlGroup*)control.Parent)->Children;
		size_t index = children.find(&control);
		if (index == children.Size || index == 0)
			return;
		ControlWithConstraints& ref = children[index - 1];
		dependencies.put(&ref.Constraints.Height);
		graph.add(this);
	}
}
