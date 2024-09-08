#pragma once

#include "ui/control/ControlGroup.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class WindowFrame:public ControlGroup {
    public:
        WindowFrame() {}

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;
    };

    class WindowContainer:Widget {
    public:

    };
}