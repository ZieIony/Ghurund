#pragma once

#include "core/ScopedPointer.h"
#include "ui/Theme.h"
#include "ui/control/LinearLayout.h"
#include "ui/control/StackLayout.h"
#include "ui/control/ColorView.h"
#include "ui/control/TextView.h"
#include "ui/widget/button/ImageButton.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class TitleBar:public StackLayout {
    private:
        ScopedPointer<ColorView> backgroundView;
        ScopedPointer<HorizontalLayout> row;
        ScopedPointer<ImageButton> closeButton;
        ScopedPointer<TextView> title;

    public:
        TitleBar(Theme& theme) {
            PreferredSize.height = PreferredSize::Height::WRAP;
            row = ghnew HorizontalLayout();
            row->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                title = ghnew TextView(theme.textViewPrimaryStyle);
                title->PreferredSize.width = PreferredSize::Width::FILL;
                closeButton = ghnew ImageButton(theme);
                //closeButton->Image = 
            }
            row->Children = { title, closeButton };
            backgroundView = ghnew ColorView(theme.getColorAccent());
            Children = { backgroundView, row };
        }

        String& getText() {
            return title->Text;
        }

        void setText(const String& text) {
            title->Text = text;
        }

        __declspec(property(get = getText, put = setText)) String& Text;
    };
}