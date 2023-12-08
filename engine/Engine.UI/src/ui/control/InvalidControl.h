#pragma once

#include "core/Color.h"

#include "Control.h"
#include "ui/StrokeStyle.h"
#include "ui/constraint/ParentConstraint.h"

namespace Ghurund::UI {
	class InvalidControl:public Control {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = InvalidControl::GET_TYPE();
#pragma endregion

	protected:
		Color backgroundColor = Color(0.2f, 1, 0, 0);
		Color borderColor = Color(1.0f, 1, 0, 0);
		std::unique_ptr<IStrokeStyle> strokeStyle;

		virtual void onContextChanged() {
			__super::onContextChanged();
			if (Context) {
				Array<float> dashes = { 3.0f, 4.0f };
				strokeStyle.reset(Context->makeStrokeStyle(dashes));
			}
		}

	public:
		InvalidControl() {
			setConstraints({
				.width = []() {
					auto constraint = makeShared<ParentWidthConstraint>();
					constraint->Min = 18;
					return constraint;
				}(),
				.height = []() {
					auto constraint = makeShared<ParentWidthConstraint>();
					constraint->Min = 18;
					return constraint;
				}()
				});
		}

		virtual void onDraw(ICanvas& canvas) override;
	};
}