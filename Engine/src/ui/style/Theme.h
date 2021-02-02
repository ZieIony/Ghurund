#pragma once

#include "core/SharedPointer.h"

#include "ui/style/Style.h"
#include "ui/control/Control.h"
#include "ui/control/TextBlockStyle.h"
#include "ui/drawable/BitmapImage.h"
#include "ui/widget/SeparatorStyle.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/menu/ToolbarLayout.h"
#include "ui/widget/tab/TabContainerLayout.h"

namespace Ghurund::UI {
    class Theme {
    private:
        static const inline float emphasis_high = 0.87f;
        static const inline float emphasis_medium = 0.6f;
        static const inline float emphasis_disabled = 0.38f;

        static const inline float highlight = 0.25f;

        static const inline float state_normal = 0.12f;
        static const inline float state_activated = 0.4f;
        static const inline float state_disabled = 0.08f;

        constexpr uint32_t colorWithAlpha(float alpha, uint32_t color) const {
            uint32_t a = (uint32_t)(alpha * 0xff);
            return ((a & 0xff) << 24) | (color & 0xffffff);
        }

        PointerMap<WString, TextStyle*> textStyles;
        Map<WString, Color> colors;
        PointerMap<WString, BitmapImage*> images;

    public:
        static inline const WString IMAGE_CHECKBOX_CHECKED = L"checkBox_checked";
        static inline const WString IMAGE_CHECKBOX_UNCHECKED = L"checkBox_unchecked";
        static inline const WString IMAGE_RADIOBUTTON_CHECKED = L"radioButton_checked";
        static inline const WString IMAGE_RADIOBUTTON_UNCHECKED = L"radioButton_unchecked";
        static inline const WString IMAGE_ARROWUP = L"arrowUp";
        static inline const WString IMAGE_ARROWDOWN = L"arrowDown";

        static inline const WString TEXTSTYLE_BUTTON = L"button";
        static inline const WString TEXTSTYLE_LIST_HEADER = L"listHeader";
        static inline const WString TEXTSTYLE_TEXT_PRIMARY = L"textPrimary";
        static inline const WString TEXTSTYLE_TEXT_SECONDARY = L"textSecondary";

        static inline const WString COLOR_ERROR = L"error";
        static inline const WString COLOR_BACKGR0UND = L"background";
        static inline const WString COLOR_CONTROL = L"control";
        static inline const WString COLOR_ACCENT = L"accent";
        static inline const WString COLOR_ON_ERROR = L"onError";
        static inline const WString COLOR_ON_BACKGR0UND = L"onBackground";
        static inline const WString COLOR_ON_ACCENT = L"onAccent";

        Style<Separator>* separatorStyle = ghnew HorizontalSeparatorStyle();
        Style<ProgressBar>* progressBarStyle = ghnew ProgressBarStyle();

        Style<TextBlock>* textViewPrimaryStyle = ghnew TextBlockPrimaryStyle();
        Style<TextBlock>* textViewSecondaryStyle = ghnew TextBlockSecondaryStyle();
        Style<TextBlock>* textViewHeaderStyle = ghnew TextBlockHeaderStyle();

        virtual ~Theme() {
            delete separatorStyle;
            delete progressBarStyle;

            delete textViewPrimaryStyle;
            delete textViewSecondaryStyle;
            delete textViewHeaderStyle;
        }

        inline PointerMap<WString, TextStyle*>& getTextStyles() {
            return textStyles;
        }

        __declspec(property(get = getTextStyles)) PointerMap<WString, TextStyle*>& TextStyles;

        inline Map<WString, Color>& getColors() {
            return colors;
        }

        __declspec(property(get = getColors)) Map<WString, Color>& Colors;

        inline PointerMap<WString, BitmapImage*>& getImages() {
            return images;
        }

        __declspec(property(get = getImages)) PointerMap<WString, BitmapImage*>& Images;

        uint32_t getColorControlNormal() {
            return colorWithAlpha(state_normal, Colors[COLOR_CONTROL]);
        }

        __declspec(property(get = getColorControlNormal)) uint32_t ColorControlNormal;

        uint32_t getColorControlDisabled() {
            return colorWithAlpha(state_disabled, Colors[COLOR_CONTROL]);
        }

        __declspec(property(get = getColorControlDisabled)) uint32_t ColorControlDisabled;

        uint32_t getColorControlActivated() {
            return colorWithAlpha(state_activated, Colors[COLOR_CONTROL]);
        }

        __declspec(property(get = getColorControlActivated)) uint32_t ColorControlActivated;

        uint32_t getColorForegroundPrimaryOnError() {
            return colorWithAlpha(emphasis_high, Colors[COLOR_ON_ERROR]);
        }

        __declspec(property(get = getColorForegroundPrimaryOnError)) uint32_t ColorForegroundPrimaryOnError;

        uint32_t getColorForegroundPrimaryOnBackground() {
            return colorWithAlpha(emphasis_high, Colors[COLOR_ON_BACKGR0UND]);
        }

        __declspec(property(get = getColorForegroundPrimaryOnBackground)) uint32_t ColorForegroundPrimaryOnBackground;

        uint32_t getColorForegroundPrimaryOnAccent() {
            return colorWithAlpha(emphasis_high, Colors[COLOR_ON_ACCENT]);
        }

        __declspec(property(get = getColorForegroundPrimaryOnAccent)) uint32_t ColorForegroundPrimaryOnAccent;

        uint32_t getColorForegroundSecondaryOnError() {
            return colorWithAlpha(emphasis_medium, Colors[COLOR_ON_ERROR]);
        }

        __declspec(property(get = getColorForegroundSecondaryOnError)) uint32_t ColorForegroundSecondaryOnError;

        uint32_t getColorForegroundSecondaryOnBackground() {
            return colorWithAlpha(emphasis_medium, Colors[COLOR_ON_BACKGR0UND]);
        }

        __declspec(property(get = getColorForegroundSecondaryOnBackground)) uint32_t ColorForegroundSecondaryOnBackground;

        uint32_t getColorForegroundSecondaryOnAccent() {
            return colorWithAlpha(emphasis_medium, Colors[COLOR_ON_ACCENT]);
        }

        __declspec(property(get = getColorForegroundSecondaryOnAccent)) uint32_t ColorForegroundSecondaryOnAccent;

        uint32_t getColorForegroundDisabledOnError() {
            return colorWithAlpha(emphasis_disabled, Colors[COLOR_ON_ERROR]);
        }

        __declspec(property(get = getColorForegroundDisabledOnError)) uint32_t ColorForegroundDisabledOnError;

        uint32_t getColorForegroundDisabledOnBackground() {
            return colorWithAlpha(emphasis_disabled, Colors[COLOR_ON_BACKGR0UND]);
        }

        __declspec(property(get = getColorForegroundDisabledOnBackground)) uint32_t ColorForegroundDisabledOnBackground;

        uint32_t getColorForegroundDisabledOnAccent() {
            return colorWithAlpha(emphasis_disabled, Colors[COLOR_ON_ACCENT]);
        }

        __declspec(property(get = getColorForegroundDisabledOnAccent)) uint32_t ColorForegroundDisabledOnAccent;

        // highlights

        uint32_t getColorHighlightOnError() {
            return colorWithAlpha(highlight, Colors[COLOR_ON_ERROR]);
        }

        __declspec(property(get = getColorHighlightOnError)) uint32_t ColorHighlightOnError;

        uint32_t getColorHighlightOnBackground() {
            return colorWithAlpha(highlight, Colors[COLOR_ACCENT]);
        }

        __declspec(property(get = getColorHighlightOnBackground)) uint32_t ColorHighlightOnBackground;

        uint32_t getColorHighlightOnAccent() {
            return colorWithAlpha(highlight, Colors[COLOR_ON_ACCENT]);
        }

        __declspec(property(get = getColorHighlightOnAccent)) uint32_t ColorHighlightOnAccent;

    };
}