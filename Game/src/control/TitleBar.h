#pragma once

#include "ui/style/Theme.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/ColorView.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/button/ImageButton.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class TitleBar:public StackLayout {
    private:
        SharedPointer<ColorView> backgroundView;
        SharedPointer<HorizontalLayout> row;
        SharedPointer<ImageButton> closeButton;
        SharedPointer<TextBlock> title;
        SharedPointer<BitmapImage> closeIcon;

    public:
        TitleBar(Ghurund::UI::Theme& theme) {
            PreferredSize.height = PreferredSize::Height::WRAP;
            row = ghnew HorizontalLayout();
            row->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                title = ghnew TextBlock(theme.textViewPrimaryStyle);
                title->PreferredSize.width = PreferredSize::Width::FILL;
                title->TextColor = theme.getColorForegroundPrimaryOnAccent();
//                closeIcon = ghnew BitmapImage(L"icons/close 18.png");
                closeButton = ghnew ImageButton(ghnew ImageButtonFlatLayout());
              //  closeButton->Image = closeIcon;
                //closeButton->Image->Tint = theme.getColorForegroundPrimaryOnAccent();
            }
            row->Alignment.vertical = Alignment::Vertical::CENTER;
            row->Children = { title, closeButton };
            backgroundView = ghnew ColorView(theme.getColorAccent());
            Children = { backgroundView, row };
        }

        inline WString& getText() {
            return title->Text;
        }

        inline void setText(const WString& text) {
            title->Text = text;
        }

        __declspec(property(get = getText, put = setText)) WString& Text;
    };
}