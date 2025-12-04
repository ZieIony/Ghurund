#pragma once

#include "LayoutManager.h"

#include "ui/adapter/AdapterLayout.h"
#include "ui/control/ControlGroup.h"

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

		void addChild(size_t adapterPosition, size_t groupPosition);

		void addLeft();
		void removeLeft();
		void addRight(float height);
		void removeRight(float height);

	public:
		AdapterLayout* adapterLayout;

		virtual bool onLayout(float x, float y, float width, float height) override;

		virtual bool onScroll(float dx, float dy);
	};
}