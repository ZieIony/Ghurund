#pragma once

#include "ui/Color.h"
#include "Status.h"

namespace Ghurund::UI {
    class WindowsTheme {
    private:
        WindowsTheme() = delete;

        static inline Color accentDark1 = 0;
        static inline Color accentDark2 = 0;
        static inline Color accentDark3 = 0;
        static inline Color accentLight1 = 0;
        static inline Color accentLight2 = 0;
        static inline Color accentLight3 = 0;
        static inline Color accentColor = 0;

    public:
        static Status init();

        static Color getAccentColor() { return accentColor; }

        static Color getAccentDark1() { return accentDark1; }
        static Color getAccentDark2() { return accentDark2; }
        static Color getAccentDark3() { return accentDark3; }

        static Color getAccentLight1() { return accentLight1; }
        static Color getAccentLight2() { return accentLight2; }
        static Color getAccentLight3() { return accentLight3; }
    };
}