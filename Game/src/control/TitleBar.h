#pragma once

#include "ui/Theme.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/ColorView.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/button/ImageButton.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class TitleBar:public StackLayout {
    private:
        ScopedPointer<ColorView> backgroundView;
        ScopedPointer<HorizontalLayout> row;
        ScopedPointer<ImageButton> closeButton;
        ScopedPointer<TextBlock> title;
        Gdiplus::Image* closeIcon;

    public:
        TitleBar(Theme& theme) {
            PreferredSize.height = PreferredSize::Height::WRAP;
            row = ghnew HorizontalLayout();
            row->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                title = ghnew TextBlock(theme.textViewPrimaryStyle);
                title->PreferredSize.width = PreferredSize::Width::FILL;
                title->TextColor = theme.getColorForegroundPrimaryOnAccent();
                closeIcon = new Gdiplus::Image(L"icons/close 18.png");
                BitmapImage* closeIconImage = ghnew BitmapImage(closeIcon);
                closeButton = ghnew ImageButton(ghnew ImageButtonFlatLayout(theme));
                closeButton->Image = closeIconImage;
                closeButton->ImageTint = theme.getColorForegroundPrimaryOnAccent();
            }
            row->Alignment.vertical = Alignment::Vertical::CENTER;
            row->Children = { title, closeButton };
            backgroundView = ghnew ColorView(theme.getColorAccent());
            Children = { backgroundView, row };
        }

        inline String& getText() {
            return title->Text;
        }

        inline void setText(const String& text) {
            title->Text = text;
        }

        __declspec(property(get = getText, put = setText)) String& Text;
    };
}