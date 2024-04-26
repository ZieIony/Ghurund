#include "ghuipch.h"
#include "AnimatedConstraint.h"

#include "ConstraintGraph.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& AnimatedConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<AnimatedConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	inline void AnimatedConstraint::resolve(Control& control, ConstraintGraph& graph) {
		evaluated = false;
		graph.add(this);
		from->resolve(control, graph);
		to->resolve(control, graph);
	}
}