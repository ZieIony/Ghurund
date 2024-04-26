#pragma once

#include "ui/control/ControlGroup.h"
#include "LayoutManager.h"
#include <ui/adapter/AdapterLayout.h>

namespace Ghurund::UI {
	class HorizontalLayoutManager:public LayoutManager {
	private:
		float spacing = 0.0f;

	public:
		inline float getSpacing() const {
			return spacing;
		}

		inline void setSpacing(float spacing) {
			this->spacing = spacing;
		}

		__declspec(property(get = getSpacing, put = setSpacing)) float Spacing;

		virtual PartialConstraintSet makeDefaultConstraints() const override;
	};

	class HorizontalAdapterLayoutManager:public HorizontalLayoutManager {
	private:
		size_t leftPosition = 0, rightPosition = 0;

	public:
		AdapterLayout* adapterLayout;

		virtual bool onLayout(float x, float y, float width, float height) override {
			ControlCollection& children = adapterLayout->Children;
			if (children.Size == 0) {
				leftPosition = 0;
				rightPosition = 0;
				adapterLayout->addChild(leftPosition, 0);
			}
			while (leftPosition > 0 && children[0].Constraints.Left.Value > 0) {
				leftPosition--;
				adapterLayout->addChild(leftPosition, 0);
			}
			while (children[0].Constraints.Right.Value <= 0) {
				adapterLayout->removeChild(0, leftPosition);
				leftPosition++;
			}
			while (rightPosition < adapterLayout->ItemAdapter->Size - 1 && children[children.Size - 1].Constraints.Right.Value < width) {
				rightPosition++;
				adapterLayout->addChild(rightPosition, children.Size);
			}
			while (children[children.Size - 1].Constraints.Left.Value >= width) {
				adapterLayout->removeChild(children.Size - 1, rightPosition);
				rightPosition--;
			}
			return true;
		}

		virtual bool onScroll(float dx, float dy) {
			scroll.x += dx;
			scroll.y += dy;
			return true;
		}
	};
}