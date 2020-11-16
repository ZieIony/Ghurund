#pragma once

#include "ui/Theme.h"
#include "ui/layout/ManualLayout.h"
#include "ui/widget/DragHelper.h"
#include "ui/window/WindowFrame.h"

using namespace Ghurund;
using namespace Ghurund::UI;

namespace Ghurund::Editor {
    class WindowsTestTab:public ManualLayout {
    private:
        DragHelper* helper;

    public:
        WindowsTestTab(Theme& theme) {
            ScopedPointer<ColorView> content = ghnew ColorView(0xffff0000);
            ScopedPointer<WindowFrame> frame = ghnew WindowFrame();
            frame->PreferredSize = { 200,150 };
            frame->Position = { 50,50 };
            frame->Child = content;
            Children = { frame };
            helper = ghnew DragHelper(*content, *frame);
        }
    };
}
