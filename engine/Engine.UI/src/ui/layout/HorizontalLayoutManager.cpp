#include "ghuipch.h"
#include "HorizontalLayoutManager.h"

#include <ui/constraint/PreviousConstraint.h>

namespace Ghurund::UI {

	PartialConstraintSet HorizontalLayoutManager::makeDefaultConstraints() const {
		return ConstraintSetInitializer{
			.left = [&]() {
			auto constraint = makeShared<PreviousRightConstraint>();
			constraint->Offset = spacing;
			return constraint;
		}(),
			.width = makeShared<WrapWidthConstraint>(),
			.height = makeShared<WrapHeightConstraint>()
		};
	}
}
