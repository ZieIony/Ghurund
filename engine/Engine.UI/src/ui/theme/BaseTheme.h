#pragma once

#include "Theme.h"

#include "core/resource/ResourceManager.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/Border.h"
#include "ui/control/Shadow.h"
#include "ui/control/Control.h"
#include "ui/control/DrawableView.h"
#include "ui/text/TextFormat.h"
#include "ui/widget/ClickResponseView.h"
#include "ui/widget/ExpandableContainer.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/StateIndicator.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/image/Bitmap.h"
#include "ui/loading/DrawableFactory.h"

namespace Ghurund::UI {
	class BaseTheme:public Ghurund::UI::Theme {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		
	public:
		BaseTheme(Ghurund::Core::ResourceManager& resourceManager, Ghurund::UI::DrawableFactory& drawableFactory);
	};
}