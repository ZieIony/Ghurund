#pragma once

#include "Theme.h"

#include "core/resource/ResourceManager.h"
#include "ui/control/Border.h"
#include "ui/control/Shadow.h"
#include "ui/control/Control.h"
#include "ui/control/DrawableView.h"
#include "ui/text/TextBlockStyle.h"
#include "ui/text/TextFormat.h"
#include "ui/widget/ClickResponseView.h"
#include "ui/widget/ExpandableContainer.h"
#include "ui/widget/SeparatorStyle.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/StateIndicator.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/image/Bitmap.h"
#include "ui/loading/DrawableFactory.h"
#include <ui/control/DrawableViewStyle.h>

namespace Ghurund::UI {
	class BaseTheme:public Ghurund::UI::Theme {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		
		CheckBoxStyle checkBoxStyle;
		ExpandableCheckBoxStyle expandableCheckBoxStyle;
		RadioButtonStyle radioButtonStyle;

		SeparatorHorizontalStyle separatorHorizontalStyle;
		SeparatorVerticalStyle separatorVerticalStyle;
		ProgressBarStyle progressBarStyle;

		TextBlockButtonStyle textViewButtonStyle;
		TextBlockPrimaryStyle textViewPrimaryStyle;
		TextBlockSecondaryStyle textViewSecondaryStyle;
		TextBlockHeaderStyle textViewHeaderStyle;
		TextBlockButtonOnAccentStyle textViewButtonOnAccentStyle;
		TextBlockPrimaryOnAccentStyle textViewPrimaryOnAccentStyle;
		TextBlockSecondaryOnAccentStyle textViewSecondaryOnAccentStyle;
		TextBlockHeaderOnAccentStyle textViewHeaderOnAccentStyle;

		ColorViewControlStyle colorViewControlStyle;
		ColorViewAccentStyle colorViewAccentStyle;
		ColorViewBackgroundStyle colorViewBackgroundStyle;

		DrawableViewStyle drawableViewStyle;
		DrawableViewOnBackgroundStyle drawableViewOnBackgroundStyle;
		DrawableViewOnAccentStyle drawableViewOnAccentStyle;
		DrawableViewAccentStyle drawableViewAccentStyle;

		BorderOnBackgroundStyle borderOnBackgroundStyle;
		BorderAccentStyle borderAccentStyle;
		ShadowButtonStyle shadowButtonStyle;
		ClickResponseViewOnBackgroundStyle clickResponseViewOnBackgroundStyle;
		ClickResponseViewOnAccentStyle clickResponseViewOnAccentStyle;
		StateIndicatorOnBackgroundStyle stateIndicatorOnBackgroundStyle;
		StateIndicatorOnAccentStyle stateIndicatorOnAccentStyle;

	public:
		BaseTheme(Ghurund::Core::ResourceManager& resourceManager, DrawableFactory& drawableFactory);
	};
}