#include "ghuipch.h"
#include "HorizontalLayoutManager.h"

#include "ui/constraint/ContentConstraint.h"
#include "ui/constraint/PreviousConstraint.h"
#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {

	PartialConstraintSet HorizontalLayoutManager::makeDefaultConstraints() const {
		return ConstraintSetInitializer{
			.left = [&]() {
			auto constraint = makeIntrusive<PreviousRightConstraint>();
			constraint->Offset = spacing;
			return constraint;
		}(),
			.width = makeIntrusive<ContentWidthConstraint>(),
			.height = makeIntrusive<ContentHeightConstraint>()
		};
	}

	void HorizontalAdapterLayoutManager::addLeft() {
		ControlCollection& children = adapterLayout->Children;
		while (leftPosition > 0 && children[0].Constraints.Left.Value > -scroll.x) {
			leftPosition--;
			adapterLayout->addChild(leftPosition, 0);
			auto& child = children[0];
			((ValueConstraint&)child.Constraints.Left).Value = children[1].Constraints.Left.Value - child.Constraints.Height.Value - Spacing;
			ConstraintGraph graph;
			((ValueConstraint&)child.Constraints.Right).resolve(*child.control.get(), graph);
			((ValueConstraint&)child.Constraints.Right).evaluate();
			child.control->layout(
				child.Constraints.Left.Value,
				0,
				child.Constraints.Width.Value,
				child.Constraints.Height.Value
			);
		}
	}

	void HorizontalAdapterLayoutManager::removeLeft() {
		ControlCollection& children = adapterLayout->Children;
		while (children.Size > 0 && children[0].Constraints.Right.Value < -scroll.x) {
			adapterLayout->removeChild(0, leftPosition);
			leftPosition++;
		}
	}

	void HorizontalAdapterLayoutManager::addRight(float width) {
		ControlCollection& children = adapterLayout->Children;
		while (rightPosition < adapterLayout->ItemAdapter.Size - 1 && children[children.Size - 1].Constraints.Right.Value < width - scroll.x) {
			rightPosition++;
			adapterLayout->addChild(rightPosition, children.Size);
			auto& child = children[children.Size - 1];
			((ValueConstraint&)child.Constraints.Left).Value = children[children.Size - 2].Constraints.Right.Value + Spacing;
			((ValueConstraint&)child.Constraints.Right).evaluate();
			child.control->layout(
				child.Constraints.Left.Value,
				0,
				child.Constraints.Width.Value,
				child.Constraints.Height.Value
			);
		}
	}

	void HorizontalAdapterLayoutManager::removeRight(float width) {
		ControlCollection& children = adapterLayout->Children;
		while (children.Size > 0 && children[children.Size - 1].Constraints.Left.Value > width - scroll.x) {
			adapterLayout->removeChild(children.Size - 1, rightPosition);
			rightPosition--;
		}
	}

	bool HorizontalAdapterLayoutManager::onLayout(float x, float y, float width, float height) {
		ControlCollection& children = adapterLayout->Children;
		if (children.Size == 0) {
			leftPosition = 0;
			rightPosition = 0;
			adapterLayout->addChild(leftPosition, 0);
			auto& child = children[0];
			((ValueConstraint&)child.Constraints.Right).Value = child.Constraints.Height.Value;
			child.control->layout(0, 0, child.Constraints.Width.Value, child.Constraints.Height.Value);
			addRight(width);
			return true;
		}
		return false;
	}

	bool HorizontalAdapterLayoutManager::onScroll(float dx, float dy) {
		if (dx == 0.0f)
			return false;
		float width = adapterLayout->Size.Height;
		ControlCollection& children = adapterLayout->Children;
		if (dx > 0) {
			if (leftPosition == 0 && children[0].Constraints.Left.Value == -scroll.x)
				return false;
			scroll.x += dx;
			addLeft();
			removeRight(width);
			auto& child = children[0];
			if (leftPosition == 0 && child.Constraints.Left.Value < scroll.x)
				scroll.x = -child.Constraints.Left.Value;
		} else {
			if (rightPosition == adapterLayout->ItemAdapter.Size - 1 && children[children.Size - 1].Constraints.Right.Value == width - scroll.x)
				return false;
			scroll.x += dx;
			addRight(width);
			removeLeft();
			auto& child = children[children.Size - 1];
			if (rightPosition == adapterLayout->ItemAdapter.Size - 1 && child.Constraints.Right.Value > width - scroll.x)
				scroll.x = width - child.Constraints.Left.Value;
		}
		return true;
	}
}
