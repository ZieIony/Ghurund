#pragma once

#include "ui/control/PaddingContainer.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class WindowFrame:public PaddingContainer {
    public:
        WindowFrame(): PaddingContainer(4) {}

        virtual bool dispatchMouseMotionEvent(const Ghurund::MouseMotionEventArgs& event) override;
    };

    class WindowContainerLayout:public WidgetLayout {
    public:
        WindowContainerLayout() {}
        WindowContainerLayout(Control* control) {}
    };

    class WindowContainer:Widget<WindowContainerLayout> {
    public:

    };
}