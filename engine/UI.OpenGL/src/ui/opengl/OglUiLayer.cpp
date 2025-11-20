#include "ghuioglpch.h"
#include "OglUiLayer.h"
#include "OglUiContext.h"

namespace Ghurund::UI::OpenGL {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& OglUiLayer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<OglUiLayer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void OglUiLayer::init(Window& window) {
        if (context)
            return;
        __super::init(*context);
        context = ghnew OglUiContext(window);
    }

    void OglUiLayer::uninit() {
        if (!context)
            return;
        delete context;
        context = nullptr;
        __super::uninit();
    }
}