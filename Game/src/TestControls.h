#pragma once

#include "MusicPlayer.h"

#include "core/ScopedPointer.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/CheckBoxRadioLayout.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/button/RadioGroup.h"
#include "ui/widget/button/ImageButton.h"
#include "ui/widget/button/TextButton.h"
#include "ui/widget/TextView.h"
#include "ui/widget/TextField.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/menu/DropDown.h"

using namespace Ghurund;
using namespace Ghurund::UI;
using namespace Ghurund::Editor;

class TestControls:public VerticalLayout {
private:
    RadioGroup radioGroup;
    ScopedPointer<MusicPlayer> player;

public:
    TestControls(Theme& theme, ResourceManager& resourceManager, ResourceContext& resourceContext) {
        Name = "controls tab";
        {
            FontPtr latoLight = ghnew Ghurund::UI::Font("fonts/lato_light.ttf", "Lato Light", 40, FW_LIGHT, false);
            TextBlockPtr textView = ghnew TextBlock("big light text", latoLight);
            ScopedPointer<TextView> textView2 = ghnew TextView();
            textView2->PreferredSize.width = PreferredSize::Width::FILL;
            textView2->Font = theme.getSecondaryTextFont();
            textView2->Text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
            textView2->Focusable = true;

            ScopedPointer<TextField> textField = ghnew TextField(theme);
            textField->Text = "type here";
            ScopedPointer<TextField> textField2 = ghnew TextField(theme);
            textField2->Text = "type here too";

            CheckBoxTextPtr checkBox = ghnew CheckBoxText(ghnew TextCheckBoxLayout(theme));
            checkBox->Text = "check me";

            RadioTextButtonPtr radioButton = ghnew RadioTextButton(theme);
            radioButton->Text = "option 1";
            RadioTextButtonPtr radioButton2 = ghnew RadioTextButton(theme);
            radioButton2->Text = "option 2";
            radioGroup = { radioButton, radioButton2 };

            ScopedPointer<ImageButton> imageButton = ghnew ImageButton(ghnew ImageButtonLayout(theme));
            //ImagePtr saveIcon = ghnew GdiImage(L"icons/icon save 32.png");
         //   imageButton->Image = saveIcon;

            player = ghnew MusicPlayer(theme);

            TextButtonPtr flatButton = ghnew TextButton(ghnew TextButtonFlatLayout(theme));
            flatButton->Text = "Submit";
            TextButtonPtr accentButton = ghnew TextButton(ghnew TextButtonAccentLayout(theme));
            accentButton->Text = "OK";

            ScopedPointer<Style<Separator>> separatorStyle = ghnew HorizontalSeparatorStyle(theme);
            ScopedPointer<Separator> separator = ghnew Separator(separatorStyle);

            ScopedPointer<ProgressBar> progressBar = ghnew ProgressBar(*theme.progressBarStyle);
            progressBar->Indeterminate = true;

            Children = {
                textView,
                textView2,
                textField,
                textField2,
                makeSpace(),
                checkBox,
                makeSpace(),
                radioButton,
                radioButton2,
                separator,
                imageButton,
                makeSpace(),
                player,
                makeSpace(),
                flatButton,
                makeSpace(),
                accentButton,
                makeSpace(),
                progressBar
            };
        }

    }
};