#include "ghuipch.h"
#include "VerticalLayoutManager.h"

#include "ui/constraint/ContentConstraint.h"
#include "ui/constraint/PreviousConstraint.h"
#include "ui/constraint/ConstraintGraph.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::UI {

	PartialConstraintSet VerticalLayoutManager::makeDefaultConstraints() const {
		return ConstraintSetInitializer{
			.width = makeIntrusive<ContentWidthConstraint>(),
			.top = [&]() {
				auto constraint = makeIntrusive<PreviousBottomConstraint>();
				constraint->Offset = spacing;
				return constraint;
			}(),
			.height = makeIntrusive<ContentHeightConstraint>()
		};
	}

	void VerticalAdapterLayoutManager::addTop() {
		ControlCollection& children = adapterLayout->Children;
		while (topPosition > 0 && children[0].Constraints.Top.Value > -scroll.y) {
			topPosition--;
			adapterLayout->addChild(topPosition, 0);
			auto& child = children[0];
			((ValueConstraint&)child.Constraints.Top).Value = children[1].Constraints.Top.Value - child.Constraints.Height.Value - Spacing;
			ConstraintGraph graph;
			((ValueConstraint&)child.Constraints.Bottom).resolve(*child.control.get(), graph);
			((ValueConstraint&)child.Constraints.Bottom).evaluate();
			child.control->layout(
				0,
				child.Constraints.Top.Value,
				child.Constraints.Width.Value,
				child.Constraints.Height.Value
			);
		}
	}

	void VerticalAdapterLayoutManager::removeTop() {
		ControlCollection& children = adapterLayout->Children;
		while (children.Size > 0 && children[0].Constraints.Bottom.Value < -scroll.y) {
			adapterLayout->removeChild(0, topPosition);
			topPosition++;
		}
	}

	void VerticalAdapterLayoutManager::addBottom(float height) {
		ControlCollection& children = adapterLayout->Children;
		while (bottomPosition < adapterLayout->ItemAdapter.Size - 1 && children[children.Size - 1].Constraints.Bottom.Value < height - scroll.y) {
			bottomPosition++;
			adapterLayout->addChild(bottomPosition, children.Size);
			auto& child = children[children.Size - 1];
			((ValueConstraint&)child.Constraints.Top).Value = children[children.Size - 2].Constraints.Bottom.Value + Spacing;
			((ValueConstraint&)child.Constraints.Bottom).evaluate();
			child.control->layout(
				0,
				child.Constraints.Top.Value,
				child.Constraints.Width.Value,
				child.Constraints.Height.Value
			);
		}
	}

	void VerticalAdapterLayoutManager::removeBottom(float height) {
		ControlCollection& children = adapterLayout->Children;
		while (children.Size > 0 && children[children.Size - 1].Constraints.Top.Value > height - scroll.y) {
			adapterLayout->removeChild(children.Size - 1, bottomPosition);
			bottomPosition--;
		}
	}

	bool VerticalAdapterLayoutManager::onLayout(float x, float y, float width, float height) {
		ControlCollection& children = adapterLayout->Children;
		if (children.Size == 0) {
			topPosition = 0;
			bottomPosition = 0;
			adapterLayout->addChild(topPosition, 0);
			auto& child = children[0];
			((ValueConstraint&)child.Constraints.Bottom).Value = child.Constraints.Height.Value;
			child.control->layout(0, 0, child.Constraints.Width.Value, child.Constraints.Height.Value);
			addBottom(height);
			return true;
		}
		return false;
	}

	bool VerticalAdapterLayoutManager::onScroll(float dx, float dy) {
		if (dy == 0.0f)
			return false;
		float height = adapterLayout->Size.Height;
		ControlCollection& children = adapterLayout->Children;
		if (dy > 0) {
			if (topPosition == 0 && children[0].Constraints.Top.Value == -scroll.y)
				return false;
			scroll.y += dy;
			addTop();
			removeBottom(height);
			auto& child = children[0];
			if (topPosition == 0 && child.Constraints.Top.Value < scroll.y)
				scroll.y = -child.Constraints.Top.Value;
		} else {
			if (bottomPosition == adapterLayout->ItemAdapter.Size - 1 && children[children.Size - 1].Constraints.Bottom.Value == height - scroll.y)
				return false;
			scroll.y += dy;
			addBottom(height);
			removeTop();
			auto& child = children[children.Size - 1];
			if (bottomPosition == adapterLayout->ItemAdapter.Size - 1 && child.Constraints.Bottom.Value > height - scroll.y)
				scroll.y = height - child.Constraints.Top.Value;
		}
		return true;
	}
}