#include "ghuipch.h"
#include "BaseTheme.h"
#include "FileLayoutProvider.h"
#include "FileDrawableProvider.h"

namespace Ghurund::UI {
	BaseTheme::BaseTheme(Ghurund::Core::ResourceManager& resourceManager, Ghurund::UI::DrawableFactory& drawableFactory):Theme(), resourceManager(resourceManager) {
		auto buttonLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/ButtonDefaultLayout.xml");
		Layouts.set(LayoutKey(Button::GET_TYPE().Name), std::make_shared<FileLayoutProvider>(resourceManager, buttonLayoutPath));
		auto checkBoxLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/CheckBoxLayout.xml");
		Layouts.set(LayoutKey(CheckBox::GET_TYPE().Name), std::make_shared<FileLayoutProvider>(resourceManager, checkBoxLayoutPath));
		auto radioLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/RadioButtonLayout.xml");
		Layouts.set(LayoutKey(RadioButton::GET_TYPE().Name), std::make_shared<FileLayoutProvider>(resourceManager, radioLayoutPath));
		auto expandableContainerLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/ExpandableContainer.xml");
		Layouts.set(LayoutKey(ExpandableContainer::GET_TYPE().Name), std::make_shared<FileLayoutProvider>(resourceManager, expandableContainerLayoutPath));

		auto latoMediumPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_medium.ttf");
		Ghurund::Core::SharedPointer<Ghurund::UI::Font> latoMediumFont(resourceManager.load<Ghurund::UI::Font>(latoMediumPath, DirectoryPath()));
		auto latoLightPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_light.ttf");
		Ghurund::Core::SharedPointer<Ghurund::UI::Font> latoLightFont(resourceManager.load<Ghurund::UI::Font>(latoLightPath, DirectoryPath()));

		/*auto buttonFont = Ghurund::Core::makeShared<TextFormat>(latoMediumFont, 10.0f, FW_MEDIUM);    // TODO: should medium font use FW_MEDIUM or FW_REGULAR?
		buttonFont->init(dwriteFactory);
		TextFormats.set(Theme::TEXTFORMAT_BUTTON, buttonFont);

		auto listHeaderFont = Ghurund::Core::makeShared<TextFormat>(latoLightFont, 14.0f, FW_LIGHT);
		listHeaderFont->init(dwriteFactory);
		TextFormats.set(Theme::TEXTFORMAT_LIST_HEADER, listHeaderFont);

		auto textPrimaryFont = Ghurund::Core::makeShared<TextFormat>(latoMediumFont, 11.0f, FW_REGULAR);
		textPrimaryFont->init(dwriteFactory);
		TextFormats.set(Theme::TEXTFORMAT_TEXT_PRIMARY, textPrimaryFont);

		auto textSecondaryFont = Ghurund::Core::makeShared<TextFormat>(latoMediumFont, 10.0f, FW_REGULAR);
		textSecondaryFont->init(dwriteFactory);
		TextFormats.set(Theme::TEXTFORMAT_TEXT_SECONDARY, textSecondaryFont);*/

		auto checkboxCheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\checkbox checked 18.png");
		Drawables.set(Theme::DRAWABLE_CHECKBOX_CHECKED, std::make_shared<FileDrawableProvider>(drawableFactory, checkboxCheckedPath));
		auto checkBoxUncheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\checkbox unchecked 18.png");
		Drawables.set(Theme::DRAWABLE_CHECKBOX_UNCHECKED, std::make_shared<FileDrawableProvider>(drawableFactory, checkBoxUncheckedPath));
		auto radioCheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\radiobutton checked 18.png");
		Drawables.set(Theme::DRAWABLE_RADIOBUTTON_CHECKED, std::make_shared<FileDrawableProvider>(drawableFactory, radioCheckedPath));
		auto radioUncheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\radiobutton unchecked 18.png");
		Drawables.set(Theme::DRAWABLE_RADIOBUTTON_UNCHECKED, std::make_shared<FileDrawableProvider>(drawableFactory, radioUncheckedPath));
		auto arrowUpPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow up 18.png");
		Drawables.set(Theme::DRAWABLE_ARROWUP, std::make_shared<FileDrawableProvider>(drawableFactory, arrowUpPath));
		auto arrowDownPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow down 18.png");
		Drawables.set(Theme::DRAWABLE_ARROWDOWN, std::make_shared<FileDrawableProvider>(drawableFactory, arrowDownPath));
		auto arrowRightPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow right 18.png");
		Drawables.set(Theme::DRAWABLE_ARROWRIGHT, std::make_shared<FileDrawableProvider>(drawableFactory, arrowRightPath));

		Styles.set(STYLE_CHECKBOX, &checkBoxStyle);
		Styles.set(STYLE_CHECKBOX_EXPANDABLE, &expandableCheckBoxStyle);
		Styles.set(STYLE_RADIOBUTTON, &radioButtonStyle);
		Styles.set(STYLE_SEPARATOR_HORIZONTAL, &separatorHorizontalStyle);
		Styles.set(STYLE_SEPARATOR_VERTICAL, &separatorVerticalStyle);
		Styles.set(STYLE_PROGRESSBAR, &progressBarStyle);
		Styles.set(STYLE_TEXTBLOCK, &textViewPrimaryStyle);
		Styles.set(STYLE_TEXTBLOCK_BUTTON, &textViewButtonStyle);
		Styles.set(STYLE_TEXTBLOCK_PRIMARY, &textViewPrimaryStyle);
		Styles.set(STYLE_TEXTBLOCK_SECONDARY, &textViewSecondaryStyle);
		Styles.set(STYLE_TEXTBLOCK_HEADER, &textViewHeaderStyle);
		Styles.set(STYLE_TEXTBLOCK_BUTTON_ONACCENT, &textViewButtonOnAccentStyle);
		Styles.set(STYLE_TEXTBLOCK_PRIMARY_ONACCENT, &textViewPrimaryOnAccentStyle);
		Styles.set(STYLE_TEXTBLOCK_SECONDARY_ONACCENT, &textViewSecondaryOnAccentStyle);
		Styles.set(STYLE_TEXTBLOCK_HEADER_ONACCENT, &textViewHeaderOnAccentStyle);
		Styles.set(STYLE_COLORVIEW_BACKGROUND, &colorViewBackgroundStyle);
		Styles.set(STYLE_COLORVIEW_CONTROL, &colorViewControlStyle);
		Styles.set(STYLE_COLORVIEW_ACCENT, &colorViewAccentStyle);
		Styles.set(STYLE_DRAWABLEVIEW, &drawableViewStyle);
		Styles.set(STYLE_DRAWABLEVIEW_ONBACKGROUND, &drawableViewOnBackgroundStyle);
		Styles.set(STYLE_DRAWABLEVIEW_ONACCENT, &drawableViewOnAccentStyle);
		Styles.set(STYLE_DRAWABLEVIEW_ACCENT, &drawableViewAccentStyle);
		Styles.set(STYLE_BORDER_ONBACKGROUND, &borderOnBackgroundStyle);
		Styles.set(STYLE_BORDER_ACCENT, &borderAccentStyle);
		Styles.set(STYLE_SHADOW_BUTTON, &shadowButtonStyle);
		Styles.set(STYLE_CLICKRESPONSEVIEW_ONBACKGROUND, &clickResponseViewOnBackgroundStyle);
		Styles.set(STYLE_CLICKRESPONSEVIEW_ONACCENT, &clickResponseViewOnAccentStyle);
		Styles.set(STYLE_STATEINDICATOR_ONBACKGROUND, &stateIndicatorOnBackgroundStyle);
		Styles.set(STYLE_STATEINDICATOR_ONACCENT, &stateIndicatorOnAccentStyle);
	}
}
