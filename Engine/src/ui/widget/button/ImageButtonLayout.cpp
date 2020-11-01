#include "ImageButton.h"
#include "ImageButtonLayout.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void ImageButtonLayout::init() {
        __super::init();
        stack = ghnew StackLayout();
        paddingContainer->Child = imageView;
        paddingContainer->Padding.Vertical = 4;
        paddingContainer->Padding.Horizontal = 8;
        stack->PreferredSize.width = PreferredSize::Width::WRAP;
        stack->PreferredSize.height = PreferredSize::Height::WRAP;
        stack->Children = { backgroundView, border, paddingContainer };
        ClickableView->Child = stack;
        root = ClickableView;
    }

    void ImageButtonLayout::onStateChanged(Control& control) {
        paddingContainer->Padding.setAll(4.0f);
        if (!control.Enabled) {
            imageView->Tint = theme.getColorForegroundDisabledOnBackground();
            border->Color = theme.getColorForegroundDisabledOnBackground();
            backgroundView->Color = theme.getColorControlDisabled();
        } else if (ClickableView->Pressed) {
            imageView->Tint = theme.getColorForegroundPrimaryOnBackground();
            border->Color = theme.getColorAccentDark();
            backgroundView->Color = theme.getColorControlActivated();
        } else if (ClickableView->Hovered || control.Focused) {
            imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            border->Color = theme.getColorAccent();
            backgroundView->Color = theme.getColorControlNormal();
        } else {
            imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            border->Color = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.getColorControlNormal();
        }
    }

    void ImageButtonFlatLayout::onStateChanged(Control& control) {
        paddingContainer->Padding.setAll(4.0f);
        backgroundView->Color = 0;
        if (!control.Enabled) {
            imageView->Tint = theme.getColorForegroundDisabledOnBackground();
            border->Color = 0;
        } else if (ClickableView->Pressed) {
            imageView->Tint = theme.getColorForegroundPrimaryOnBackground();
            border->Color = theme.getColorAccentDark();
        } else if (ClickableView->Hovered || control.Focused) {
            imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            border->Color = theme.getColorAccent();
        } else {
            imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            border->Color = 0;
        }
    }

}
