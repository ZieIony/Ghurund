#pragma once

#include "LayoutManager.h"

#include "ui/adapter/AdapterLayout.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
	class VerticalLayoutManager:public LayoutManager {
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

	class VerticalAdapterLayoutManager:public VerticalLayoutManager {
	private:
		size_t topPosition = 0, bottomPosition = 0;

		void addChild(size_t adapterPosition, size_t groupPosition);

		void addTop();
		void removeTop();
		void addBottom(float height);
		void removeBottom(float height);

	public:
		AdapterLayout* adapterLayout;

		virtual bool onLayout(float x, float y, float width, float height) override;

		virtual bool onScroll(float dx, float dy);
	};
}