#include "TextViewStyle.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void TextViewPrimaryStyle::onStateChanged(TextView& textView) const {
        textView.Font = theme.getPrimaryTextFont();
        if (!textView.Enabled) {
            textView.TextColor = theme.getColorForegroundDisabledOnBackground();
        } else {
            textView.TextColor = theme.getColorForegroundPrimaryOnBackground();
        }
    }

    void TextViewSecondaryStyle::onStateChanged(TextView& textView) const {
        textView.Font = theme.getSecondaryTextFont();
        if (!textView.Enabled) {
            textView.TextColor = theme.getColorForegroundDisabledOnBackground();
        } else {
            textView.TextColor = theme.getColorForegroundSecondaryOnBackground();
        }
    }

    void TextViewHeaderStyle::onStateChanged(TextView& textView) const {
        textView.Font = theme.getSecondaryTextFont();
        if (!textView.Enabled) {
            textView.TextColor = theme.getColorForegroundDisabledOnBackground();
        } else {
            textView.TextColor = theme.getColorForegroundSecondaryOnBackground();
        }
    }
}