#include "core/application/Application.h"
#include "core/window/WindowClass.h"

#include "application/ApplicationWindow.h"

export namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::Core;

    class DemoWindow:public ApplicationWindow {
    public:
        DemoWindow(Ghurund::Core::Application& app, Renderer& renderer):ApplicationWindow(app, renderer) {
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