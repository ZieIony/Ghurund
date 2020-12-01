#pragma once

#include "core/SharedPointer.h"
#include "ui/Theme.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/ScrollView.h"
#include "ui/widget/button/TextButton.h"
#include "ui/layout/FlowLayout.h"

using namespace Ghurund;
using namespace Ghurund::UI;

class TestFlowLayouts:public ScrollView {
public:
    TestFlowLayouts(Theme& theme) {
        Name = "flow layouts tab";
        SharedPointer<VerticalLayout> column = ghnew VerticalLayout();
        column->PreferredSize.height = PreferredSize::Height::WRAP;
        Child = column;

        {
            StackLayoutPtr stack = ghnew StackLayout();
            stack->PreferredSize.height = PreferredSize::Height::WRAP;
            SharedPointer<Border> border = ghnew Border();
            SharedPointer<PaddingContainer> padding = ghnew PaddingContainer();
            padding->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Padding.All = 4;
            SharedPointer<FlowLayout> flowLayout = ghnew FlowLayout();
            flowLayout->PreferredSize.height = PreferredSize::Height::WRAP;
            flowLayout->Spacing = { 8,8 };
            padding->Child = flowLayout;
            stack->Children = { padding, border };
            column->Children.add(stack);

            for (size_t i = 0; i < 10; i++) {
                TextButtonPtr button = ghnew TextButton(theme);
                button->Text = fmt::format("test {}", (unsigned int)(i + 1)).c_str();
                button->MinSize = FloatSize{ 60.0f, 60.0f };
                flowLayout->Children.add(button);
            }

            flowLayout->Children[4]->Visible = false;
            flowLayout->Children[8]->PreferredSize.width = PreferredSize::Width::FILL;
        }

        column->Children.add(SharedPointer<Space>(ghnew Space()));

        {
            StackLayoutPtr stack = ghnew StackLayout();
            stack->PreferredSize.height = PreferredSize::Height::WRAP;
            SharedPointer<Border> border = ghnew Border();
            SharedPointer<PaddingContainer> padding = ghnew PaddingContainer();
            padding->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Padding.All = 4;
            SharedPointer<FlowLayout> flowLayout = ghnew FlowLayout();
            flowLayout->ReverseLayout = true;
            flowLayout->PreferredSize.height = PreferredSize::Height::WRAP;
            flowLayout->Spacing = { 8,8 };
            padding->Child = flowLayout;
            stack->Children = { padding, border };
            column->Children.add(stack);

            for (size_t i = 0; i < 10; i++) {
                TextButtonPtr button = ghnew TextButton(ghnew TextButtonAccentLayout(theme));
                button->Text = fmt::format("test {}", (unsigned int)(i + 1)).c_str();
                flowLayout->Children.add(button);
            }

            flowLayout->Children[4]->Visible = false;
            flowLayout->Children[8]->PreferredSize.width = PreferredSize::Width::FILL;
        }
    }
};