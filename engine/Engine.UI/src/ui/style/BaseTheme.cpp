#include "ghuipch.h"
#include "BaseTheme.h"

namespace Ghurund::UI {
	void BaseTheme::loadImage(ImageDrawableFactory& drawableFactory, const DrawableKey& key, const Ghurund::Core::FilePath& path) {
		Ghurund::Core::SharedPointer<Drawable> imageDrawable(drawableFactory.makeDrawable(path));
		if (imageDrawable.get())
			Drawables.set(key, imageDrawable);
	}

	BaseTheme::BaseTheme(Ghurund::Core::ResourceManager& resourceManager, ImageDrawableFactory& drawableFactory) {
		Ghurund::Core::SharedPointer<Ghurund::UI::Font> latoMediumFont(resourceManager.load<Ghurund::UI::Font>(Ghurund::Core::FilePath(L"lib://Ghurund/fonts\\lato_medium.ttf")));
		Ghurund::Core::SharedPointer<Ghurund::UI::Font> latoLightFont(resourceManager.load<Ghurund::UI::Font>(Ghurund::Core::FilePath(L"lib://Ghurund/fonts\\lato_light.ttf")));

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

		loadImage(drawableFactory, Theme::DRAWABLE_CHECKBOX_CHECKED, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\checkbox checked 18.png"));
		loadImage(drawableFactory, Theme::DRAWABLE_CHECKBOX_UNCHECKED, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\checkbox unchecked 18.png"));
		loadImage(drawableFactory, Theme::DRAWABLE_RADIOBUTTON_CHECKED, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\radiobutton checked 18.png"));
		loadImage(drawableFactory, Theme::DRAWABLE_RADIOBUTTON_UNCHECKED, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\radiobutton unchecked 18.png"));
		loadImage(drawableFactory, Theme::DRAWABLE_ARROWUP, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\arrow up 18.png"));
		loadImage(drawableFactory, Theme::DRAWABLE_ARROWDOWN, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\arrow down 18.png"));
		loadImage(drawableFactory, Theme::DRAWABLE_ARROWRIGHT, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\arrow right 18.png"));

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
