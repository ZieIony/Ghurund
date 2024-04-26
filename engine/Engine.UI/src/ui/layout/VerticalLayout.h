#pragma once

#include "ui/control/ControlGroup.h"
#include "VerticalLayoutManager.h"

namespace Ghurund::UI {
	class VerticalLayout:public ControlGroup {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = VerticalLayout::GET_TYPE();
#pragma endregion

	private:
		float spacing = 0.0f;

	public:
		VerticalLayout() {
			layoutManager = ghnew VerticalLayoutManager();
		}

		inline float getSpacing() const {
			return spacing;
		}

		inline void setSpacing(float spacing) {
			this->spacing = spacing;
		}

		__declspec(property(get = getSpacing, put = setSpacing)) float Spacing;
	};
}