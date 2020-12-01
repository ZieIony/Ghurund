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

    protected:
        Map<String, StateHandler> stateHandlers;
        Ghurund::SharedPointer<Ghurund::UI::Font> buttonFont, listHeaderFont, primaryTextFont, secondaryTextFont;
        BitmapImage* checkBoxChecked, * checkBoxUnchecked;
        BitmapImage* radioButtonChecked, * radioButtonUnchecked;
        BitmapImage* arrowUp, * arrowDown;

    public:
        Style<Separator>* separatorStyle = ghnew HorizontalSeparatorStyle(*this);
        Style<ProgressBar>* progressBarStyle = ghnew ProgressBarStyle(*this);

        Style<TextBlock>* textViewPrimaryStyle = ghnew TextBlockPrimaryStyle(*this);
        Style<TextBlock>* textViewSecondaryStyle = ghnew TextBlockSecondaryStyle(*this);
        Style<TextBlock>* textViewHeaderStyle = ghnew TextBlockHeaderStyle(*this);

        virtual ~Theme() {
            separatorStyle->release();
            progressBarStyle->release();

            textViewPrimaryStyle->release();
            textViewSecondaryStyle->release();
            textViewHeaderStyle->release();
        }

        inline Map<String, StateHandler>& getStateHandlers() {
            return stateHandlers;
        }

        __declspec(property(get = getStateHandlers)) Map<String, StateHandler>& StateHandlers;

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

        inline Ghurund::UI::Font* getButtonFont() {
            return buttonFont;
        }

        __declspec(property(get = getButtonFont)) Ghurund::UI::Font* ButtonFont;

        inline Ghurund::UI::Font* getPrimaryTextFont() {
            return primaryTextFont;
        }

        inline Ghurund::UI::Font* getSecondaryTextFont() {
            return secondaryTextFont;
        }

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

        __declspec(property(get = ColorControlActivated)) uint32_t ColorControlActivated;

        uint32_t getColorForegroundPrimaryOnError() const {
            return colorWithAlpha(emphasis_high, getColorOnError());
        }
        uint32_t getColorForegroundPrimaryOnBackground() const {
            return colorWithAlpha(emphasis_high, getColorOnBackground());
        }
        uint32_t getColorForegroundPrimaryOnAccent() const {
            return colorWithAlpha(emphasis_high, getColorOnAccent());
        }

        uint32_t getColorForegroundSecondaryOnError() const {
            return colorWithAlpha(emphasis_medium, getColorOnError());
        }
        uint32_t getColorForegroundSecondaryOnBackground() const {
            return colorWithAlpha(emphasis_medium, getColorOnBackground());
        }
        uint32_t getColorForegroundSecondaryOnAccent() const {
            return colorWithAlpha(emphasis_medium, getColorOnAccent());
        }

        uint32_t getColorForegroundDisabledOnError() const {
            return colorWithAlpha(emphasis_disabled, getColorOnError());
        }
        uint32_t getColorForegroundDisabledOnBackground() const {
            return colorWithAlpha(emphasis_disabled, getColorOnBackground());
        }
        uint32_t getColorForegroundDisabledOnAccent() const {
            return colorWithAlpha(emphasis_disabled, getColorOnAccent());
        }

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