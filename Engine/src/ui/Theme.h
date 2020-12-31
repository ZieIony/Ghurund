#pragma once

#include "core/SharedPointer.h"

#include "ui/Style.h"
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

    protected:
        SharedPointer<BitmapImage> checkBoxChecked, checkBoxUnchecked;
        SharedPointer<BitmapImage> radioButtonChecked, radioButtonUnchecked;
        SharedPointer<BitmapImage> arrowUp, arrowDown;

    public:
        static inline const WString TEXTSTYLE_BUTTON = "button";
        static inline const WString TEXTSTYLE_LIST_HEADER = "listHeader";
        static inline const WString TEXTSTYLE_TEXT_PRIMARY = "textPrimary";
        static inline const WString TEXTSTYLE_TEXT_SECONDARY = "textSecondary";

        Style2<Separator>* separatorStyle = ghnew HorizontalSeparatorStyle();
        Style<ProgressBar>* progressBarStyle = ghnew ProgressBarStyle(*this);

        Style2<TextBlock>* textViewPrimaryStyle = ghnew TextBlockPrimaryStyle();
        Style2<TextBlock>* textViewSecondaryStyle = ghnew TextBlockSecondaryStyle();
        Style2<TextBlock>* textViewHeaderStyle = ghnew TextBlockHeaderStyle();

        virtual ~Theme() {
            delete separatorStyle;
            progressBarStyle->release();

            delete textViewPrimaryStyle;
            delete textViewSecondaryStyle;
            delete textViewHeaderStyle;
        }

        virtual uint32_t getColorError() const = 0;

        __declspec(property(get = getColorError)) uint32_t ColorError;

        virtual uint32_t getColorBackground() const = 0;

        __declspec(property(get = getColorBackground)) uint32_t ColorBackground;

        virtual uint32_t getColorControl() const = 0;

        __declspec(property(get = getColorControl)) uint32_t ColorControl;

        virtual uint32_t getColorAccent() const = 0;

        __declspec(property(get = getColorAccent)) uint32_t ColorAccent;

        virtual uint32_t getColorAccentDark() const = 0;

        __declspec(property(get = getColorAccentDark)) uint32_t ColorAccentDark;

        virtual uint32_t getColorOnError() const = 0;

        __declspec(property(get = getColorOnError)) uint32_t ColorOnError;

        virtual uint32_t getColorOnBackground() const = 0;

        __declspec(property(get = getColorOnBackground)) uint32_t ColorOnBackground;

        virtual uint32_t getColorOnAccent() const = 0;

        __declspec(property(get = getColorOnAccent)) uint32_t ColorOnAccent;

        inline PointerMap<WString, TextStyle*>& getTextStyles() {
            return textStyles;
        }

        __declspec(property(get = getTextStyles)) PointerMap<WString, TextStyle*>& TextStyles;

        inline BitmapImage* getCheckBoxChecked() {
            return checkBoxChecked;
        }

        __declspec(property(get = getCheckBoxChecked)) BitmapImage* CheckBoxChecked;

        inline BitmapImage* getCheckBoxUnchecked() {
            return checkBoxUnchecked;
        }

        __declspec(property(get = getCheckBoxUnchecked)) BitmapImage* CheckBoxUnchecked;

        inline BitmapImage* getRadioButtonChecked() {
            return radioButtonChecked;
        }

        __declspec(property(get = getRadioButtonChecked)) BitmapImage* RadioButtonChecked;

        inline BitmapImage* getRadioButtonUnchecked() {
            return radioButtonUnchecked;
        }

        __declspec(property(get = getRadioButtonUnchecked)) BitmapImage* RadioButtonUnchecked;

        inline BitmapImage* getArrowUp() {
            return arrowUp;
        }

        __declspec(property(get = getArrowUp)) BitmapImage* ArrowUp;

        inline BitmapImage* getArrowDown() {
            return arrowDown;
        }

        __declspec(property(get = getArrowDown)) BitmapImage* ArrowDown;

        uint32_t getColorControlNormal() const {
            return colorWithAlpha(state_normal, getColorControl());
        }

        __declspec(property(get = getColorControlNormal)) uint32_t ColorControlNormal;

        uint32_t getColorControlDisabled() const {
            return colorWithAlpha(state_disabled, getColorControl());
        }

        __declspec(property(get = getColorControlDisabled)) uint32_t ColorControlDisabled;

        uint32_t getColorControlActivated() const {
            return colorWithAlpha(state_activated, getColorControl());
        }

        __declspec(property(get = getColorControlActivated)) uint32_t ColorControlActivated;

        uint32_t getColorForegroundPrimaryOnError() const {
            return colorWithAlpha(emphasis_high, getColorOnError());
        }

        __declspec(property(get = getColorForegroundPrimaryOnError)) uint32_t ColorForegroundPrimaryOnError;

        uint32_t getColorForegroundPrimaryOnBackground() const {
            return colorWithAlpha(emphasis_high, getColorOnBackground());
        }

        __declspec(property(get = getColorForegroundPrimaryOnBackground)) uint32_t ColorForegroundPrimaryOnBackground;

        uint32_t getColorForegroundPrimaryOnAccent() const {
            return colorWithAlpha(emphasis_high, getColorOnAccent());
        }

        __declspec(property(get = getColorForegroundPrimaryOnAccent)) uint32_t ColorForegroundPrimaryOnAccent;

        uint32_t getColorForegroundSecondaryOnError() const {
            return colorWithAlpha(emphasis_medium, getColorOnError());
        }

        __declspec(property(get = getColorForegroundSecondaryOnError)) uint32_t ColorForegroundSecondaryOnError;

        uint32_t getColorForegroundSecondaryOnBackground() const {
            return colorWithAlpha(emphasis_medium, getColorOnBackground());
        }

        __declspec(property(get = getColorForegroundSecondaryOnBackground)) uint32_t ColorForegroundSecondaryOnBackground;

        uint32_t getColorForegroundSecondaryOnAccent() const {
            return colorWithAlpha(emphasis_medium, getColorOnAccent());
        }

        __declspec(property(get = getColorForegroundSecondaryOnAccent)) uint32_t ColorForegroundSecondaryOnAccent;

        uint32_t getColorForegroundDisabledOnError() const {
            return colorWithAlpha(emphasis_disabled, getColorOnError());
        }

        __declspec(property(get = getColorForegroundDisabledOnError)) uint32_t ColorForegroundDisabledOnError;

        uint32_t getColorForegroundDisabledOnBackground() const {
            return colorWithAlpha(emphasis_disabled, getColorOnBackground());
        }

        __declspec(property(get = getColorForegroundDisabledOnBackground)) uint32_t ColorForegroundDisabledOnBackground;

        uint32_t getColorForegroundDisabledOnAccent() const {
            return colorWithAlpha(emphasis_disabled, getColorOnAccent());
        }

        __declspec(property(get = getColorForegroundDisabledOnAccent)) uint32_t ColorForegroundDisabledOnAccent;

        // highlights

        uint32_t getColorHighlightOnError() const {
            return colorWithAlpha(highlight, getColorOnError());
        }

        __declspec(property(get = getColorHighlightOnError)) uint32_t ColorHighlightOnError;

        uint32_t getColorHighlightOnBackground() const {
            return colorWithAlpha(highlight, getColorAccent());
        }

        __declspec(property(get = getColorHighlightOnBackground)) uint32_t ColorHighlightOnBackground;

        uint32_t getColorHighlightOnAccent() const {
            return colorWithAlpha(highlight, getColorOnAccent());
        }

        __declspec(property(get = getColorHighlightOnAccent)) uint32_t ColorHighlightOnAccent;

    };
}