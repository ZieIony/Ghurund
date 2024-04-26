#pragma once

#include "ui/control/ControlGroup.h"
#include "HorizontalLayoutManager.h"

namespace Ghurund::UI {
	class HorizontalLayout:public ControlGroup {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = HorizontalLayout::GET_TYPE();
#pragma endregion

	public:
		HorizontalLayout() {
			layoutManager = ghnew HorizontalLayoutManager();
		}

		inline float getSpacing() const {
			return ((HorizontalLayoutManager*)layoutManager)->Spacing;
		}

		inline void setSpacing(float spacing) {
			((HorizontalLayoutManager*)layoutManager)->Spacing = spacing;
		}

		__declspec(property(get = getSpacing, put = setSpacing)) float Spacing;
	};
}