#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
	class CheckBox:public CheckBoxRadio {
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
		Event<CheckBox, bool> checkedChanged = *this;

		CheckBox() {
			interactionHandler.clicked += [this](InteractionHandler&, const MouseClickedEventArgs&) {
				Checked = !checked;
				return true;
			};
		}

        inline void setChecked(bool checked) {
            if (this->checked != checked) {
                this->checked = checked;
                dispatchStateChanged();
                checkedChanged(checked);
            }
        }

        __declspec(property(put = setChecked)) bool Checked;
	};
}