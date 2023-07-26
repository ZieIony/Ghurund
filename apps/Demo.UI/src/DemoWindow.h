#include "core/application/Application.h"
#include "core/window/WindowClass.h"

#include "application/UIApplicationWindow.h"

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::Core;

    class DemoWindow:public UIApplicationWindow {
    public:
        DemoWindow(Ghurund::Core::Application& app, Renderer& renderer):UIApplicationWindow(app, renderer) {
            Style = WindowStyle{
             .hasMinimizeButton = true,
             .hasMaximizeButton = true,
             .hasTitle = true,
             .borderStyle = WindowBorderStyle::RESIZE,
             .showOnTaskbar = true
            };
        }
    };
}