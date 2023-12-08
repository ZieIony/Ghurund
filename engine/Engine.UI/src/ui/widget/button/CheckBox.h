#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
	class CheckBox:public CheckBoxRadio<CheckBox> {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CheckBox::GET_TYPE();
#pragma endregion

	protected:
		virtual void onStateChanged() override;

	public:
		CheckBox() {
			interactionHandler.clicked += [this](InteractionHandler&, const MouseClickedEventArgs&) {
				Checked = !checked;
				return true;
			};
		}
	};
}