#include "ImageButton.h"
#include "ImageButtonLayout.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void ImageButtonLayout::init() {
        __super::init();
        stack = ghnew StackLayout();
        paddingContainer->Child = imageView;
        paddingContainer->Padding.All = 4;
        stack->PreferredSize.width = PreferredSize::Width::WRAP;
        stack->PreferredSize.height = PreferredSize::Height::WRAP;
        clickResponseView = makeScoped<ClickResponseView>(theme.ColorHighlightOnBackground);
        stack->Children = { backgroundView, clickResponseView, border, paddingContainer };
        ClickableView->Child = stack;
        root = ClickableView;
    }

    void ImageButtonLayout::onStateChanged(Control& control) {
        if (!control.Enabled) {
            imageView->Tint = theme.getColorForegroundDisabledOnBackground();
            border->Color = theme.getColorForegroundDisabledOnBackground();
            backgroundView->Color = theme.getColorControlDisabled();
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            border->Color = theme.getColorAccent();
            backgroundView->Color = theme.getColorControlNormal();
        } else {
            imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            border->Color = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.getColorControlNormal();
        }
        clickResponseView->Pressed = ClickableView->Pressed;
    }

    void ImageButtonFlatLayout::onStateChanged(Control& control) {
        backgroundView->Color = 0;
        if (!control.Enabled) {
            imageView->Tint = theme.getColorForegroundDisabledOnBackground();
            border->Color = 0;
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            border->Color = theme.getColorAccent();
        } else {
            imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            border->Color = 0;
        }
        clickResponseView->Pressed = ClickableView->Pressed;
    }

}
