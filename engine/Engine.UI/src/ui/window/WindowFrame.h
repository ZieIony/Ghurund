#pragma once

#include "ui/control/PaddingContainer.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class WindowFrame:public PaddingContainer {
    public:
        WindowFrame(): PaddingContainer(4) {}

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;
    };

    class WindowContainer:Widget {
    public:

    };
}