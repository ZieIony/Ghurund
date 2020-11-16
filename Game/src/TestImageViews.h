#pragma once

#include "core/ScopedPointer.h"
#include "ui/Theme.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/ScrollView.h"
#include "ui/control/Space.h"
#include "ui/widget/VerticalScrollBar.h"

using namespace Ghurund;
using namespace Ghurund::UI;

class TestImageViews:public HorizontalLayout {
    ScopedPointer<ScrollView> scrollView;
    VerticalScrollBarPtr scrollBar;

public:
    TestImageViews(Ghurund::UI::Theme& theme) {
        scrollView = ghnew ScrollView();
        scrollView->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        scrollBar = ghnew VerticalScrollBar(theme);
        scrollBar->OnScrolled.add([this](Control& control) {
            scrollView->Scroll = { 0.0f, scrollBar->Scroll };
            scrollView->repaint();
            return true;
        });
        scrollView->OnScrolled.add([this](Control& control) {
            scrollBar->Scroll = scrollView->Scroll.y;
            scrollBar->repaint();
            return true;
        });
        scrollView->OnSizeChanged.add([this](Control& control) {
            scrollBar->MaxScroll = scrollView->MaxScroll.y;
            scrollBar->repaint();
            return true;
        });

        Name = "image views tab";
        {
            const char* texts[4] = {
                "ScaleMode::NONE",
                "ScaleMode::STRETCH",
                "ScaleMode::FIT",
                "ScaleMode::CROP"
            };
            ScopedPointer<VerticalLayout> column = ghnew VerticalLayout();
            column->PreferredSize.height = PreferredSize::Height::WRAP;
            ScopedPointer<BitmapImage> image = ghnew BitmapImage("images/game.png");
            for (unsigned int i = 0; i < 4; i++) {
                StackLayoutPtr stack = ghnew StackLayout();
                stack->PreferredSize = { 200, 120 };
                ScopedPointer<Border> border = ghnew Border();
                ScopedPointer<ImageView> imageView = ghnew ImageView();
                imageView->Image = image;
                imageView->ScaleMode = (enum ImageScaleMode)i;
                stack->Children = { imageView, border };
                ScopedPointer<TextBlock> textView = ghnew TextBlock(theme.textViewSecondaryStyle);
                textView->Text = texts[i];

                column->Children.addAll({
                    textView,
                    stack,
                    ScopedPointer<Space>(ghnew Space(16.0f))
                    });
            }
            scrollView->Child = column;
        }

        Children = { scrollView, scrollBar };
    }
};