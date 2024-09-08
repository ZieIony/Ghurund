#include "ghuipch.h"
#include "ParentConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/Canvas.h"
#include "ui/UIDebugTools.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ParentLeftConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ParentLeftConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

#ifdef _DEBUG
	void ParentLeftConstraint::draw(ICanvas& canvas, float x, float y, float width, float height) const {
		if (offset != 0) {
			canvas.Color = UIDebugTools::colorConstraints2;
			canvas.drawLine(0, y + height / 2, value, y + height / 2, 1, UIDebugTools::getStrokeStyle3());
			canvas.drawLine(value, y + height / 2 - 5, value, y + height / 2 + 5, 1);
		}
		__super::draw(canvas, x, y, width, height);
	}
#endif

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

#ifdef _DEBUG
	void ParentRightConstraint::draw(ICanvas& canvas, float x, float y, float width, float height) const {
		if (offset != 0) {
			canvas.Color = UIDebugTools::colorConstraints2;
			canvas.drawLine(value - offset, y + height / 2, value, y + height / 2, 1, UIDebugTools::getStrokeStyle3());
			canvas.drawLine(value, y + height / 2 - 5, value, y + height / 2 + 5, 1);
		}
		__super::draw(canvas, x, y, width, height);
	}
#endif

	const Ghurund::Core::Type& ParentTopConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ParentTopConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

#ifdef _DEBUG
	void ParentTopConstraint::draw(ICanvas& canvas, float x, float y, float width, float height) const {
		if (offset != 0) {
			canvas.Color = UIDebugTools::colorConstraints2;
			canvas.drawLine(x + width / 2, 0, x + width / 2, value, 1, UIDebugTools::getStrokeStyle3());
			canvas.drawLine(x + width / 2 - 5, value, x + width / 2 + 5, value, 1);
		}
		__super::draw(canvas, x, y, width, height);
	}
#endif

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

#ifdef _DEBUG
	void ParentBottomConstraint::draw(ICanvas& canvas, float x, float y, float width, float height) const {
		if (offset != 0) {
			canvas.Color = UIDebugTools::colorConstraints2;
			canvas.drawLine(x + width / 2, value - offset, x + width / 2, value, 1, UIDebugTools::getStrokeStyle3());
			canvas.drawLine(x + width / 2 - 5, value, x + width / 2 + 5, value, 1);
		}
		__super::draw(canvas, x, y, width, height);
	}
#endif

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
