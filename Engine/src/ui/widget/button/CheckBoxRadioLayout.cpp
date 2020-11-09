#include "CheckBoxRadioLayout.h"
#include "ui\Theme.h"

namespace Ghurund::UI {
    void CheckBoxRadioLayout::init() {
        selectableView = ghnew Ghurund::UI::SelectableView();
        imageView = ghnew Ghurund::UI::ImageView();
        selectableView->Child = imageView;
        root = selectableView;
    }

    void CheckBoxRadioLayout::onStateChanged(Control& control) {
        if (!control.Enabled) {
            imageView->Tint = theme.getColorForegroundDisabledOnBackground();
        } else if (selectableView->Pressed) {
            if (selectableView->Selected) {
                imageView->Tint = theme.getColorAccentDark();
            } else {
                imageView->Tint = theme.getColorForegroundPrimaryOnBackground();
            }
        } else if (selectableView->Hovered || selectableView->Focused) {
            if (selectableView->Selected) {
                imageView->Tint = theme.getColorAccent();
            } else {
                imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            }
        } else {
            if (selectableView->Selected) {
                imageView->Tint = theme.getColorAccent();
            } else {
                imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            }
        }
    }

    void CheckBoxLayout::onStateChanged(Control& control) {
        if (selectableView->Selected) {
            imageView->Image = theme.CheckBoxChecked;
        } else {
            imageView->Image = theme.CheckBoxUnchecked;
        }
        __super::onStateChanged(control);
    }
    
    void RadioButtonLayout::onStateChanged(Control& control) {
        if (selectableView->Selected) {
            imageView->Image = theme.getRadioButtonChecked();
        } else {
            imageView->Image = theme.getRadioButtonUnchecked();
        }
        __super::onStateChanged(control);
    }

    void CheckBoxRadioTextLayout::init() {
        selectableView = ghnew Ghurund::UI::SelectableView();
        ScopedPointer<HorizontalLayout> row = ghnew HorizontalLayout();
        row->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);
        textView = ghnew Ghurund::UI::TextBlock();
        imageView = ghnew Ghurund::UI::ImageView();
        ScopedPointer<Space> space = ghnew Space();
        row->Children = { imageView, space, textView };
        row->Alignment.vertical = Alignment::Vertical::CENTER;
        selectableView->Child = row;
        root = selectableView;
    }

    void CheckBoxRadioTextLayout::onStateChanged(Control& control) {
        textView->Font = theme.getButtonFont();
        if (!control.Enabled) {
            imageView->Tint = theme.getColorForegroundDisabledOnBackground();
            textView->TextColor = theme.getColorForegroundDisabledOnBackground();
        } else if (selectableView->Pressed) {
            if (selectableView->Selected) {
                imageView->Tint = theme.getColorAccentDark();
            } else {
                imageView->Tint = theme.getColorForegroundPrimaryOnBackground();
            }
            textView->TextColor = theme.getColorForegroundPrimaryOnBackground();
        } else if (selectableView->Hovered || selectableView->Focused) {
            if (selectableView->Selected) {
                imageView->Tint = theme.getColorAccent();
            } else {
                imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            }
            textView->TextColor = theme.getColorForegroundSecondaryOnBackground();
        } else {
            if (selectableView->Selected) {
                imageView->Tint = theme.getColorAccent();
            } else {
                imageView->Tint = theme.getColorForegroundSecondaryOnBackground();
            }
            textView->TextColor = theme.getColorForegroundSecondaryOnBackground();
        }
    }

    void TextCheckBoxLayout::onStateChanged(Control& control) {
        if (selectableView->Selected) {
            imageView->Image = theme.CheckBoxChecked;
        } else {
            imageView->Image = theme.CheckBoxUnchecked;
        }
        __super::onStateChanged(control);
    }

    void RadioTextButtonLayout::onStateChanged(Control& control) {
        if (selectableView->Selected) {
            imageView->Image = theme.RadioButtonChecked;
        } else {
            imageView->Image = theme.RadioButtonUnchecked;
        }
        __super::onStateChanged(control);
    }
}
