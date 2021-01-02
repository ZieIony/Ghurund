#include "MenuBarLayout.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void MenuBarWithBackgroundLayout::init() {
        __super::init();
        stack = ghnew StackLayout();
        backgroundView = ghnew ColorView();
        backgroundView->Color = theme.getColorBackground();
        stack->Children = { backgroundView, recyclerView };
        root = stack;
    }
}
