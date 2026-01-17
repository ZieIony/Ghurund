#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
	class CheckBox:public CheckBoxRadio {
#pragma region reflection
	private:
		static Property<CheckBox, bool> PROPERTY_IS_CHECKED;
		BindableProperty isCheckedProperty = BindableProperty(*this, PROPERTY_IS_CHECKED);

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
				IsChecked = !checked;
				return true;
			};
			bindableProperties.add(isCheckedProperty);
		}

        inline void setIsChecked(bool checked) {
            if (this->checked != checked) {
                this->checked = checked;
                dispatchStateChanged();
				isCheckedProperty.PropertyChanged(&checked);
                checkedChanged(checked);
            }
        }

        __declspec(property(put = setIsChecked)) bool IsChecked;
	};
}