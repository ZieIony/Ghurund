#include "ghuipch.h"
#include "Theme.h"

#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/ExpandableContainer.h"

namespace Ghurund::UI {
    void Theme::updateColors() {
        colors.put(COLOR_CONTROL, lerpColors(Colors[COLOR_BACKGR0UND], Colors[COLOR_FOREGROUND_ONBACKGROUND], state_normal));
        colors.put(COLOR_PRIMARY_ONBACKGROUND, colorWithAlpha(emphasis_high, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.put(COLOR_SECONDARY_ONBACKGROUND, colorWithAlpha(emphasis_medium, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.put(COLOR_DISABLED_ONBACKGROUND, colorWithAlpha(emphasis_disabled, Colors[COLOR_FOREGROUND_ONBACKGROUND]));
        colors.put(COLOR_HIGHLIGHT_ONBACKGROUND, colorWithAlpha(highlight, Colors[COLOR_ACCENT]));
        colors.put(COLOR_PRIMARY_ONACCENT, colorWithAlpha(emphasis_high, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.put(COLOR_SECONDARY_ONACCENT, colorWithAlpha(emphasis_medium, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.put(COLOR_DISABLED_ONACCENT, colorWithAlpha(emphasis_disabled, Colors[COLOR_FOREGROUND_ONACCENT]));
        colors.put(COLOR_HIGHLIGHT_ONACCENT, colorWithAlpha(highlight, Colors[COLOR_FOREGROUND_ONACCENT]));
    }
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Theme>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "Theme", sizeof(Ghurund::UI::Theme));
        return TYPE;
    }
}