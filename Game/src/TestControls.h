#pragma once

#include "MusicPlayer.h"

#include "core/SharedPointer.h"
#include "ui/control/ScrollView.h"
#include "ui/control/TextBlock.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/CheckBoxRadioLayout.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/button/RadioGroup.h"
#include "ui/widget/button/ImageButton.h"
#include "ui/widget/button/TextButton.h"
#include "ui/widget/textfield/TextField.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/menu/DropDown.h"

using namespace Ghurund;
using namespace Ghurund::UI;
using namespace Ghurund::Editor;

class TestControls:public ScrollView {
private:
    RadioGroup radioGroup;
    SharedPointer<MusicPlayer> player;

public:
    TestControls(Ghurund::UI::Theme& theme, ResourceManager& resourceManager, ResourceContext& resourceContext) {
        Name = "controls tab";

        SharedPointer<VerticalLayout> verticalLayout = ghnew VerticalLayout();
        verticalLayout->PreferredSize.height = PreferredSize::Height::WRAP;

        {
            SharedPointer<Font> latoLight = ghnew Ghurund::UI::Font("fonts/lato_light.ttf", "Lato Light", 40, FW_LIGHT, false);
            latoLight->init(resourceContext.Graphics2D);
            SharedPointer<TextBlock> textView = ghnew TextBlock("big light text", latoLight);
            SharedPointer<TextView> textView2 = ghnew TextView();
            textView2->PreferredSize.width = PreferredSize::Width::FILL;
            textView2->Font = theme.SecondaryTextFont;
            textView2->Text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

            SharedPointer<TextField> textField = ghnew TextField();
            textField->Text = "type here";
            SharedPointer<TextField> textField2 = ghnew TextField();
            textField2->Text = "type here too";

            SharedPointer<CheckBoxText> checkBox = ghnew CheckBoxText();
            checkBox->Text = "check me";

            RadioTextButtonPtr radioButton = ghnew RadioTextButton();
            radioButton->Text = "option 1";
            RadioTextButtonPtr radioButton2 = ghnew RadioTextButton();
            radioButton2->Text = "option 2";
            radioGroup = { radioButton, radioButton2 };

            SharedPointer<HorizontalLayout> horizontalLayout = ghnew HorizontalLayout();
            horizontalLayout->PreferredSize.height = PreferredSize::Height::WRAP;
            for (size_t i : {0, 1, 2, 3}) {
                SharedPointer<ImageButton> imageButton = ghnew ImageButton();
                SharedPointer<BitmapImage> saveIcon = BitmapImage::makeFromImage(resourceContext, L"icons/icon save 32.png");
                imageButton->Image = makeShared<BitmapImageDrawable>(saveIcon);
                horizontalLayout->Children.add(imageButton);
            }

            player = ghnew MusicPlayer(theme);

            TextButtonPtr flatButton = ghnew TextButton(ghnew TextButtonFlatLayout());
            flatButton->Text = "Submit";
            TextButtonPtr accentButton = ghnew TextButton(ghnew TextButtonAccentLayout());
            accentButton->Text = "OK";

            SharedPointer<Separator> separator = ghnew Separator(ghnew HorizontalSeparatorStyle());

            SharedPointer<ProgressBar> progressBar = ghnew ProgressBar(*theme.progressBarStyle);
            progressBar->Indeterminate = true;

            verticalLayout->Children = {
                textView,
                textView2,
                textField,
                textField2,
                makeShared<Space>(),
                checkBox,
                makeShared<Space>(),
                radioButton,
                radioButton2,
                separator,
                horizontalLayout,
                makeShared<Space>(),
                player,
                makeShared<Space>(),
                flatButton,
                makeShared<Space>(),
                accentButton,
                makeShared<Space>(),
                progressBar
            };
        }

        Child = verticalLayout;
    }
};