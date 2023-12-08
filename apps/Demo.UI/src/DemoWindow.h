#include "core/application/Application.h"
#include "core/window/WindowClass.h"

#include "application/UIApplicationWindow.h"

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::Core;

    class DemoWindow:public UIApplicationWindow {
    private:
        SharedPointer<Control> demoLayout;

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

        virtual void init(WindowManager& windowManager) override {
            __super::init(windowManager);

            demoLayout.set(Application.ResourceManager.load<Control>(
                FilePath(L"apps/Demo.UI/res/layout.xml"),
                DirectoryPath(),
                ResourceFormat::AUTO,
                LoadOption::DONT_CACHE
            ));
            Content = demoLayout.get();

            sizeChanged += [&](Window& window) {
                Logger::print(LogType::INFO, _T("\n"));
                Logger::print(LogType::INFO, demoLayout->printTree().Data);
                Logger::print(LogType::INFO, _T("\n"));
                demoLayout->validate();
                return true;
            };
        }
    };
}