#pragma once

#include "ui/constraint/ConstraintSet.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
	using namespace ::DirectX;

	class LayoutManager {
	protected:
		XMFLOAT2 scroll = { 0, 0 };

	public:
		virtual ~LayoutManager() = 0 {}

		virtual PartialConstraintSet makeDefaultConstraints() const = 0;

		virtual bool onLayout(float x, float y, float width, float height) {
			return false;
		}

		inline const XMFLOAT2& getScroll() const {
			return scroll;
		}

		__declspec(property(get = getScroll)) const XMFLOAT2& Scroll;

		virtual bool onScroll(float dx, float dy) {
			return false;
		}
	};
}
