#include "ghpch.h"
#include "Theme.h"

#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"

namespace Ghurund::UI {
    void Theme::updateColors() {
        colors.set(COLOR_CONTROL, lerpColors(Colors[COLOR_BACKGR0UND], Colors[COLOR_FOREGROUND_ONBACKGROUND], state_normal));
        colors.set(COLOR_PRIMARY_ONBACKGROUND, colorWithAlpha(emphasis_high, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.set(COLOR_SECONDARY_ONBACKGROUND, colorWithAlpha(emphasis_medium, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.set(COLOR_DISABLED_ONBACKGROUND, colorWithAlpha(emphasis_disabled, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.set(COLOR_HIGHLIGHT_ONBACKGROUND, colorWithAlpha(highlight, Colors[COLOR_ACCENT]));
        colors.set(COLOR_PRIMARY_ONACCENT, colorWithAlpha(emphasis_high, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.set(COLOR_SECONDARY_ONACCENT, colorWithAlpha(emphasis_medium, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.set(COLOR_DISABLED_ONACCENT, colorWithAlpha(emphasis_disabled, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.set(COLOR_HIGHLIGHT_ONACCENT, colorWithAlpha(highlight, Colors[COLOR_FOREGROUND_ONACCENT]));

        layouts.set(&Button::TYPE, "~/layouts/ButtonDefaultLayout.xml");
        layouts.set(&CheckBox::TYPE, "~/layouts/CheckBoxLayout.xml");
        layouts.set(&RadioButton::TYPE, "~/layouts/RadioButtonLayout.xml");
    }
}