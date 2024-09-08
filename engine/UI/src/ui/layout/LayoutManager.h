#pragma once

#include "ui/constraint/ConstraintSet.h"
#include <core/math/Point.h>

namespace Ghurund::UI {
	class LayoutManager {
	protected:
		FloatPoint scroll = { 0, 0 };

	public:
		virtual ~LayoutManager() = 0 {}

		virtual PartialConstraintSet makeDefaultConstraints() const = 0;

		virtual bool onLayout(float x, float y, float width, float height) {
			return false;
		}

		inline const FloatPoint& getScroll() const {
			return scroll;
		}

		__declspec(property(get = getScroll)) const FloatPoint& Scroll;

		virtual bool onScroll(float dx, float dy) {
			return false;
		}
	};
}