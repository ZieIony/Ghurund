#include "Theme.h"

namespace Ghurund::UI {
    Theme::Theme() {
        styles.set(STYLE_SEPARATOR_HORIZONTAL, &separatorHorizontalStyle);
        styles.set(STYLE_SEPARATOR_VERTICAL, &separatorVerticalStyle);
        styles.set(STYLE_PROGRESSBAR, &progressBarStyle);
        styles.set(STYLE_TEXTBLOCK_BUTTON, &textViewButtonStyle);
        styles.set(STYLE_TEXTBLOCK_PRIMARY, &textViewPrimaryStyle);
        styles.set(STYLE_TEXTBLOCK_SECONDARY, &textViewSecondaryStyle);
        styles.set(STYLE_TEXTBLOCK_HEADER, &textViewHeaderStyle);
        styles.set(STYLE_TEXTBLOCK_BUTTON_ONACCENT, &textViewButtonOnAccentStyle);
        styles.set(STYLE_TEXTBLOCK_PRIMARY_ONACCENT, &textViewPrimaryOnAccentStyle);
        styles.set(STYLE_TEXTBLOCK_SECONDARY_ONACCENT, &textViewSecondaryOnAccentStyle);
        styles.set(STYLE_TEXTBLOCK_HEADER_ONACCENT, &textViewHeaderOnAccentStyle);
        styles.set(STYLE_COLORVIEW_BACKGROUND, &colorViewBackgroundStyle);
        styles.set(STYLE_COLORVIEW_CONTROL, &colorViewControlStyle);
        styles.set(STYLE_COLORVIEW_ACCENT, &colorViewAccentStyle);
        styles.set(STYLE_IMAGEVIEW, &imageViewStyle);
        styles.set(STYLE_IMAGEVIEW_ONBACKGROUND, &imageViewOnBackgroundStyle);
        styles.set(STYLE_IMAGEVIEW_ONACCENT, &imageViewOnAccentStyle);
        styles.set(STYLE_IMAGEVIEW_ACCENT, &imageViewAccentStyle);
        styles.set(STYLE_BORDER_ONBACKGROUND, &borderOnBackgroundStyle);
        styles.set(STYLE_BORDER_ACCENT, &borderAccentStyle);
        styles.set(STYLE_SHADOW_BUTTON, &shadowButtonStyle);
        styles.set(STYLE_CLICKRESPONSEVIEW_ONBACKGROUND, &clickResponseViewOnBackgroundStyle);
        styles.set(STYLE_CLICKRESPONSEVIEW_ONACCENT, &clickResponseViewOnAccentStyle);
    }

    void Theme::updateColors() {
        colors.set(COLOR_CONTROL, lerpColors(state_normal, Colors[COLOR_BACKGR0UND], Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.set(COLOR_PRIMARY_ONBACKGROUND, colorWithAlpha(emphasis_high, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.set(COLOR_SECONDARY_ONBACKGROUND, colorWithAlpha(emphasis_medium, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.set(COLOR_DISABLED_ONBACKGROUND, colorWithAlpha(emphasis_disabled, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.set(COLOR_HIGHLIGHT_ONBACKGROUND, colorWithAlpha(highlight, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.set(COLOR_PRIMARY_ONACCENT, colorWithAlpha(emphasis_high, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.set(COLOR_SECONDARY_ONACCENT, colorWithAlpha(emphasis_medium, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.set(COLOR_DISABLED_ONACCENT, colorWithAlpha(emphasis_disabled, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.set(COLOR_HIGHLIGHT_ONACCENT, colorWithAlpha(highlight, Colors[COLOR_FOREGROUND_ONACCENT]));
    }
}