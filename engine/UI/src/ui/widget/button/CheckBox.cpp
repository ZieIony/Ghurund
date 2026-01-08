#include "ghuipch.h"
#include "CheckBox.h"

namespace Ghurund::UI {
	void CheckBox::onStateChanged() {
		__super::onStateChanged();
		if (checkedParameter)
			checkedParameter->Value = checked;
		if (checkedParameter2)
			checkedParameter2->Value = checked;
	}

	const Ghurund::Core::Type& CheckBox::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBox>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}