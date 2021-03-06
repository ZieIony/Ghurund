#pragma once

#include "core/SharedPointer.h"
#include "ui/style/Theme.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/ScrollView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/Border.h"
#include "ui/widget/button/Button.h"
#include "ui/layout/FlowLayout.h"
#include "ui/layout/StackLayout.h"
#include <ui/control/TextBlock.h>
#include <ui/control/Space.h>

using namespace Ghurund;
using namespace Ghurund::UI;

class TestFlowLayouts:public ScrollView {
public:
    TestFlowLayouts(ResourceContext& context, LayoutLoader& loader) {
        Name = "flow layouts tab";
        SharedPointer<VerticalLayout> column = ghnew VerticalLayout();
        column->PreferredSize.height = PreferredSize::Height::WRAP;
        Child = column;

        {
            auto stack = makeShared<StackLayout>();
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
                PointerList<Control*> controls;
                if (loader.load(FilePath(L"layouts/ButtonLayout.xml"), controls) == Status::OK) {
                    auto button = makeShared<Button>();
                    button->Layout = std::unique_ptr<ButtonBinding>(ghnew ButtonBinding(controls[0]));
                    auto buttonText = makeShared<TextBlock>();
                    //buttonText->Text = fmt::format(L"test {}", (unsigned int)(i + 1)).c_str();
                    button->Content = buttonText;
                    button->MinSize = FloatSize{ 60.0f, 60.0f };
                    flowLayout->Children.add(button);
                }
            }

            flowLayout->Children[4]->Visible = false;
            flowLayout->Children[8]->PreferredSize.width = PreferredSize::Width::FILL;
        }

        column->Children.add(SharedPointer<Space>(ghnew Space()));

        {
            SharedPointer<StackLayout> stack = ghnew StackLayout();
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
                PointerList<Control*> controls;
                if (loader.load(FilePath(L"layouts/ButtonAccentLayout.xml"), controls) == Status::OK) {
                    auto button = makeShared<Button>();
                    button->Layout = std::unique_ptr<ButtonBinding>(ghnew ButtonBinding(controls[0]));
                    auto buttonText = makeShared<TextBlock>();
                    //buttonText->Text = fmt::format(L"test {}", (unsigned int)(i + 1)).c_str();
                    button->Content = buttonText;
                    button->MinSize = FloatSize{ 60.0f, 60.0f };
                    flowLayout->Children.add(button);
                }
            }

            flowLayout->Children[4]->Visible = false;
            flowLayout->Children[8]->PreferredSize.width = PreferredSize::Width::FILL;
        }
    }
};