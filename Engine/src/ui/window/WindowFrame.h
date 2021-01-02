#pragma once

#include "ui/control/PaddingContainer.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class WindowFrame:public PaddingContainer {
    public:
        WindowFrame(): PaddingContainer(4) {}

        virtual bool dispatchMouseMotionEvent(const Ghurund::Input::MouseMotionEventArgs& event) override;
    };

    class WindowContainerLayout:public WidgetLayout {

    };

    class WindowContainer:Widget<WindowContainerLayout> {
    public:

    };
}