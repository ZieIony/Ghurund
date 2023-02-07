#pragma once

#include "Theme.h"

#include "core/resource/ResourceManager.h"
#include "ui/control/Border.h"
#include "ui/control/Shadow.h"
#include "ui/control/Control.h"
#include "ui/control/ImageView.h"
#include "ui/text/TextBlockStyle.h"
#include "ui/text/TextFormat.h"
#include "ui/widget/ClickResponseView.h"
#include "ui/widget/ExpandableContainer.h"
#include "ui/widget/SeparatorStyle.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/StateIndicator.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"

namespace Ghurund::UI {
    class BaseTheme:public Ghurund::UI::Theme {
    private:
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

        ImageViewStyle imageViewStyle;
        ImageViewOnBackgroundStyle imageViewOnBackgroundStyle;
        ImageViewOnAccentStyle imageViewOnAccentStyle;
        ImageViewAccentStyle imageViewAccentStyle;

        BorderOnBackgroundStyle borderOnBackgroundStyle;
        BorderAccentStyle borderAccentStyle;
        ShadowButtonStyle shadowButtonStyle;
        ClickResponseViewOnBackgroundStyle clickResponseViewOnBackgroundStyle;
        ClickResponseViewOnAccentStyle clickResponseViewOnAccentStyle;
        StateIndicatorOnBackgroundStyle stateIndicatorOnBackgroundStyle;
        StateIndicatorOnAccentStyle stateIndicatorOnAccentStyle;

        void loadImage(Ghurund::Core::ResourceManager& resourceManager, const ImageKey& key, const Ghurund::Core::FilePath& path) {
            /*Status result;
            Ghurund::Core::SharedPointer<Bitmap> bitmap = resourceManager.load<Bitmap>(path, nullptr, &result);
            Ghurund::Core::SharedPointer<ImageDrawable> imageDrawable = ghnew BitmapDrawable(bitmap);
            Images.set(key, imageDrawable);*/
        }

    public:
        BaseTheme(Ghurund::Core::ResourceManager& resourceManager) {
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

            loadImage(resourceManager, Theme::IMAGE_CHECKBOX_CHECKED, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\checkbox checked 18.png"));
            loadImage(resourceManager, Theme::IMAGE_CHECKBOX_UNCHECKED, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\checkbox unchecked 18.png"));
            loadImage(resourceManager, Theme::IMAGE_RADIOBUTTON_CHECKED, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\radiobutton checked 18.png"));
            loadImage(resourceManager, Theme::IMAGE_RADIOBUTTON_UNCHECKED, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\radiobutton unchecked 18.png"));
            loadImage(resourceManager, Theme::IMAGE_ARROWUP, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\arrow up 18.png"));
            loadImage(resourceManager, Theme::IMAGE_ARROWDOWN, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\arrow down 18.png"));
            loadImage(resourceManager, Theme::IMAGE_ARROWRIGHT, Ghurund::Core::FilePath(L"lib://Ghurund/icons\\arrow right 18.png"));

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
            Styles.set(STYLE_IMAGEVIEW, &imageViewStyle);
            Styles.set(STYLE_IMAGEVIEW_ONBACKGROUND, &imageViewOnBackgroundStyle);
            Styles.set(STYLE_IMAGEVIEW_ONACCENT, &imageViewOnAccentStyle);
            Styles.set(STYLE_IMAGEVIEW_ACCENT, &imageViewAccentStyle);
            Styles.set(STYLE_BORDER_ONBACKGROUND, &borderOnBackgroundStyle);
            Styles.set(STYLE_BORDER_ACCENT, &borderAccentStyle);
            Styles.set(STYLE_SHADOW_BUTTON, &shadowButtonStyle);
            Styles.set(STYLE_CLICKRESPONSEVIEW_ONBACKGROUND, &clickResponseViewOnBackgroundStyle);
            Styles.set(STYLE_CLICKRESPONSEVIEW_ONACCENT, &clickResponseViewOnAccentStyle);
            Styles.set(STYLE_STATEINDICATOR_ONBACKGROUND, &stateIndicatorOnBackgroundStyle);
            Styles.set(STYLE_STATEINDICATOR_ONACCENT, &stateIndicatorOnAccentStyle);
        }
    };
}