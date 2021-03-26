#pragma once

#include "Theme.h"

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

    public:
        BaseTheme(FontCollectionLoader& fontLoader, IDWriteFactory& dwriteFactory) {
            auto buttonFont = Ghurund::makeShared<TextFormat>(L"fonts/lato_medium.ttf", L"Lato Medium", 10.0f, FW_MEDIUM, false);
            buttonFont->init(fontLoader, dwriteFactory);
            TextFormats.set(Theme::TEXTFORMAT_BUTTON, buttonFont);

            auto listHeaderFont = Ghurund::makeShared<TextFormat>(L"fonts/lato_light.ttf", L"Lato Light", 14.0f, FW_LIGHT, false);
            listHeaderFont->init(fontLoader, dwriteFactory);
            TextFormats.set(Theme::TEXTFORMAT_LIST_HEADER, listHeaderFont);

            auto textPrimaryFont = Ghurund::makeShared<TextFormat>(L"fonts/lato_regular.ttf", L"Lato", 11.0f, FW_REGULAR, false);
            textPrimaryFont->init(fontLoader, dwriteFactory);
            TextFormats.set(Theme::TEXTFORMAT_TEXT_PRIMARY, textPrimaryFont);

            auto textSecondaryFont = Ghurund::makeShared<TextFormat>(L"fonts/lato_regular.ttf", L"Lato", 10.0f, FW_REGULAR, false);
            textSecondaryFont->init(fontLoader, dwriteFactory);
            TextFormats.set(Theme::TEXTFORMAT_TEXT_SECONDARY, textSecondaryFont);

            /*SharedPointer<Drawable> checkBoxChecked = BitmapImage::makeFromImage(context, L"icons/checkbox checked 18.png");
            Images.set(Theme::IMAGE_CHECKBOX_CHECKED, checkBoxChecked);
            SharedPointer<Drawable> checkBoxUnchecked = BitmapImage::makeFromImage(context, L"icons/checkbox unchecked 18.png");
            Images.set(Theme::IMAGE_CHECKBOX_UNCHECKED, checkBoxUnchecked);
            SharedPointer<Drawable> radioButtonChecked = BitmapImage::makeFromImage(context, L"icons/radiobutton checked 18.png");
            Images.set(Theme::IMAGE_RADIOBUTTON_CHECKED, radioButtonChecked);
            SharedPointer<Drawable> radioButtonUnchecked = BitmapImage::makeFromImage(context, L"icons/radiobutton unchecked 18.png");
            Images.set(Theme::IMAGE_RADIOBUTTON_UNCHECKED, radioButtonUnchecked);
            SharedPointer<Drawable> arrowUp = BitmapImage::makeFromImage(context, L"icons/arrow up 18.png");
            Images.set(Theme::IMAGE_ARROWUP, arrowUp);
            SharedPointer<Drawable> arrowDown = BitmapImage::makeFromImage(context, L"icons/arrow down 18.png");
            Images.set(Theme::IMAGE_ARROWDOWN, arrowDown);
            SharedPointer<Drawable> arrowRight = BitmapImage::makeFromImage(context, L"icons/arrow right 18.png");
            Images.set(Theme::IMAGE_ARROWRIGHT, arrowRight);*/

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