#pragma once

#include "core/Color.h"
#include "ui/constraint/ContentConstraint.h"
#include "ui/control/ControlContainer.h"
#include <ui/theme/AttributeKey.h>

namespace Ghurund::UI {
	class Separator:public ControlContainer {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Separator::GET_TYPE();
#pragma endregion

	protected:
		virtual void onThemeChanged() override;

		virtual void onStateChanged() override;

	public:
		Separator();

		inline void setColor(const Color& color) {
		}

		inline void setColor(const ColorKey& color) {
		}

		__declspec(property(put = setColor)) const Color& Color;

		inline float getThickness() const {
			return 0;
		}

		inline void setThickness(float thickness) {
			//colorView->MinSize = { thickness, thickness };
		}

		__declspec(property(get = getThickness, put = setThickness)) float Thickness;

		virtual PartialConstraintSet makeDefaultConstraints() const override {
			return ConstraintSetInitializer{
				.width = makeIntrusive<ParentWidthConstraint>(),
				.height = makeIntrusive<ContentHeightConstraint>()
			};
		}
	};
}