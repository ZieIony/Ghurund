#pragma once

#include "core/ScopedPointer.h"
#include "ui/Theme.h"
#include "ui/control/LinearLayout.h"
#include "ui/control/ScrollView.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/CheckBoxRadioLayout.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/button/ImageButton.h"
#include "ui/widget/button/TextButton.h"
#include "ui/widget/TextField.h"
#include "ui/widget/ProgressBar.h"

using namespace Ghurund;
using namespace Ghurund::UI;

class TestImageViews:public ScrollView {
public:
    TestImageViews(Theme& theme) {
        Name = "image views tab";
        {
            char* texts[4] = {
                "ScaleMode::NONE",
                "ScaleMode::STRETCH",
                "ScaleMode::FIT",
                "ScaleMode::CROP"
            };
            VerticalLayoutPtr column = ghnew VerticalLayout();
            column->PreferredSize.height = PreferredSize::Height::WRAP;
            ScopedPointer<GdiImage> image = ghnew GdiImage(_T("images/game.png"));
            for (unsigned int i = 0; i < 4; i++) {
                StackLayoutPtr stack = ghnew StackLayout();
                stack->setPreferredSize(200, 120);
                ScopedPointer<Border> border = ghnew Border();
                ScopedPointer<ImageView> imageView = ghnew ImageView(image);
                imageView->ScaleMode = (enum ImageScaleMode)i;
                stack->Children = { imageView, border };
                ScopedPointer<TextView> textView = ghnew TextView(theme.textViewSecondaryStyle);
                textView->Text = texts[i];
                ScopedPointer<Space> space = ghnew Space(16.0f);

                column->Children.addAll({ textView, stack, space });
            }
            Child = column;
        }

    }
};