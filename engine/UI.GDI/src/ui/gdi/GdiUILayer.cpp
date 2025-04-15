#include "ghuigdipch.h"
#include "GdiUILayer.h"

#include "UIContext.h"
#include "ui/RootView.h"

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& GdiUiLayer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GdiUiLayer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void GdiUiLayer::init(Window& window) {
        context = ghnew UiContext(window);
        __super::init(*context);
        canvas = ghnew GdiCanvas();
        canvas->init(window.Handle);
    }

    void GdiUiLayer::uninit() {
        delete canvas;
        canvas = nullptr;
        delete context;
        context = nullptr;
    }
}