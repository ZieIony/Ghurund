#include "Ghurund.Core.h"

#include "core/application/Application.h"
#include "Direct2DWindow.h"

namespace Samples {
    class SampleApplication:public Ghurund::Core::Application {
    public:
        virtual void onInit() override {
            ResourceManager.Libraries.add(L"test", DirectoryPath(L"./test"));
            ResourceManager.Libraries.add(L"icons", DirectoryPath(L"./icons"));

            auto window = ghnew Direct2DWindow(this->Timer);
            window->title = _T("Preview");
            window->Size = { Settings.get<uint32_t>("width"), Settings.get<uint32_t>("height") };
            Windows.add(window);
            window->visible = true;
            window->bringToFront();
        }
    };
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::Settings settings;
    settings.parse(GetCommandLine());
    Ghurund::Core::main<Samples::SampleApplication>(&settings);
    return 0;
}
