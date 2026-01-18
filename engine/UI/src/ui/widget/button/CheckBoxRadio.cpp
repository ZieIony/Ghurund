#include "ghuipch.h"
#include "CheckBoxRadio.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& CheckBoxRadio::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBoxRadio>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void CheckBoxRadio::onLayoutChanged() {
		iconView.set(nullptr);
		__super::onLayoutChanged();
		Control* layoutControl = layout.get();
		if (layoutControl) {
			iconView.set((Ghurund::UI::ImageView*)layoutControl->find("icon"));
			iconView->addReference();
			checkedParameter2 = (FloatInput*)iconView->Material->Inputs.get("checked");
		}
	}
	
	void CheckBoxRadio::onMaterialChanged() {
		if (material != nullptr) {
			checkedParameter = (FloatInput*)material->Inputs.get("checked");
		} else {
			checkedParameter = nullptr;
		}
	}
}