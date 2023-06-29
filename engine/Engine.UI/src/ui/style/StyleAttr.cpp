#include "ghuipch.h"
#include "Style.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {

	const Style* StyleRef::getValue(const Control& owner) const {
		auto theme = owner.Theme;
		if (theme) {
			auto index = theme->Styles.indexOfKey(key);
			if (index != theme->Styles.Size)
				return theme->Styles[key];
		}
		return nullptr;
	}

}
