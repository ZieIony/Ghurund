#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
	class CheckBox:public CheckBoxRadio<CheckBox> {
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

		virtual void onStateChanged() override;

	public:
		CheckBox() {
			interactionHandler.clicked += [this](InteractionHandler&, const MouseClickedEventArgs&) {
				Checked = !checked;
				return true;
			};
		}

		static const Ghurund::Core::Type& GET_TYPE();

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;
	};
}